#include <stdlib.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <poll.h>
#include <fcntl.h>

#define CRLF "\r\n"

struct poller_s {
    struct pollfd *fds;

    // current amount of elements in the array
    unsigned int amount;

    // size of the array
    unsigned int size;
};

struct ftp_s {
    struct poller_s *poller;

    // CONTROL socket
    int control_fd;

    // DATA socket
    int data_fd;
    int data_accepted_fd;
};

// idc
int socket_init(int port);

struct ftp_s *ftp_init(void)
{
    struct ftp_s *ftp = malloc(sizeof(struct ftp_s));

    if (ftp == NULL)
        return NULL;
    ftp->data_fd = -1;
    ftp->data_accepted_fd = -1;
    ftp->control_fd = -1;
    ftp->poller = NULL;
    return ftp;
}

struct poller_s *poller_init(unsigned int initial_size, int socket_fd)
{
    struct poller_s *poller = calloc(1, sizeof(struct poller_s));

    if (poller == NULL) {
        return NULL;
    }
    if (initial_size > 0) {
        poller->fds = calloc(initial_size, sizeof(struct pollfd));
        poller->fds[0].fd = socket_fd;
        poller->fds[0].events = POLLIN;
        poller->fds[0].revents = 0;
        poller->amount = 1;
    } else {
        poller->fds = NULL;
        poller->amount = 0;
    }
    poller->size = initial_size;
    return poller;
}

void poller_fd_add(struct poller_s *poller, int fd)
{
    if (poller->amount == poller->size) {
        poller->size += 1;
        poller->fds = realloc(poller->fds, sizeof(struct pollfd) * (poller->size));
    }
    poller->fds[poller->amount].fd = fd;
    poller->fds[poller->amount].events = POLLIN;
    poller->fds[poller->amount].revents = 0;
    poller->amount++;
}

void poller_fd_delete(struct poller_s *poller, int i)
{
    poller->fds[i] = poller->fds[poller->amount - 1];
    poller->amount--;
}

void new_client_handler(struct poller_s *poller, int socket_fd)
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int accepted_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &client_addr_len);

    if (accepted_fd == -1) {
        perror("accept");
        return;
    }
    poller_fd_add(poller, accepted_fd);
    printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
}

void client_quit(struct ftp_s *ftp, int fd, int socket_fd, unsigned int i)
{
    if (fd != socket_fd) {
        if (close(fd) == -1)
            perror("close");
        poller_fd_delete(ftp->poller, i);
        i--;
    }
}

char *get_formatted_ip(char *ip)
{
    size_t len = strlen(ip);
    for (size_t i = 0; i < len; i++) {
        if (ip[i] == '.') {
            ip[i] = ',';
        }
    }
    return ip;
}

void get_formatted_port(in_port_t *port, int *p1, int *p2)
{
    uint16_t net_port = ntohs(*port);
    *p1 = net_port / 256;
    *p2 = net_port - (*p1 * 256);
}

void client_handler(struct ftp_s *ftp, unsigned int *i, int socket_fd)
{
    size_t a = 256;
    char buffer[a];
    int fd = ftp->poller->fds[*i].fd;

    int bytes_read = read(fd, buffer, a);
    if (bytes_read <= 0) {
        client_quit(ftp, fd, socket_fd, *i);
    } else {
        buffer[bytes_read] = 0;
        if (strcmp(buffer, "PASV"CRLF) == 0) {
            ftp->data_fd = socket_init(0);
            if (ftp->data_fd == -1) {
                fprintf(stderr, "yeah i just couldn't bind fuck it\n");
                exit(84);
            }
            struct sockaddr_in socket_info;
            socklen_t socket_info_len = sizeof(socket_info);
            getsockname(ftp->data_fd, (struct sockaddr *)&socket_info, &socket_info_len);

            int p1, p2;
            get_formatted_port(&socket_info.sin_port, &p1, &p2);

            printf("The fucking port: %d\n", ntohs(socket_info.sin_port));

            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            printf("before accept\n");
            ftp->data_accepted_fd = accept(ftp->data_fd, (struct sockaddr *) &client_addr, &client_addr_len);
            printf("after accept\n");

            if (ftp->data_accepted_fd == -1) {
                perror("accept");
                return;
            }

            char buffer2[2048];
            snprintf(buffer2,
                2048,
                "227 Entering Passive Mode (%s,%d,%d)"CRLF,
                get_formatted_ip(inet_ntoa(socket_info.sin_addr)),
                p1, p2);
            if (write(fd, buffer2, strlen(buffer2)) == -1) {
                perror("write");
                return;
            }
        } else if (strncmp(buffer, "RETR ", 5) == 0) {
            // TODO: I'm pretty sure I should be forking here!
            if (ftp->data_fd == -1) {
                fprintf(stderr, "create data stream pls\n");
                return;
            }
            char *filename = strrchr(buffer, ' ') + 1;
            filename[strlen(filename) - 1] = 0;
            filename[strlen(filename) - 1] = 0;
            printf("fucking filename: %s\nsize: %zu\n", filename, strlen(filename));

            // char *filename = "Makefile";
            int file_fd = open(filename, O_RDONLY);

            if (file_fd == -1) {
                perror("open");
                return;
            }

            const char *status = "150";
            if (write(fd, status, strlen(status)) == -1) {
                perror("write");
                return;
            }

            // fuck it only buffer, no stat
            char filebuffer[4096];
            int bytes_read_file = read(file_fd, filebuffer, 4096);
            if (bytes_read_file == -1) {
                perror("read");
                return;
            }

            if (write(ftp->data_accepted_fd, filebuffer, strlen(filebuffer)) == -1) {
                perror("write");
                return;
            }

            close(file_fd);
            close(ftp->data_fd);
            close(ftp->data_accepted_fd);
            ftp->data_fd = -1;
            ftp->data_accepted_fd = -1;
        } else if (strcmp(buffer, "QUIT"CRLF) == 0) {
            client_quit(ftp, fd, socket_fd, *i);
        } else {
            const char *str = "I lost the game :3\n";
            if (write(fd, str, strlen(str)) == -1) {
                perror("write");
            }
        }
    }
}

void poller_handler(struct ftp_s *ftp)
{
    unsigned int amount = ftp->poller->amount;

    for (unsigned int i = 0; i < amount; i++) {
        if (ftp->poller->fds[i].revents & POLLIN) {
            if (ftp->poller->fds[i].fd == ftp->control_fd) {
                new_client_handler(ftp->poller, ftp->control_fd);
            } else {
                client_handler(ftp, &i, ftp->control_fd);
            }
        }
    }
}

int socket_init(int port)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        perror("socket");
        return -1;
    }

    const int enable = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        perror("setsockopt");
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(socket_fd);
        return -1;
    }

    if (listen(socket_fd, 10) < 0) {
        perror("listen");
        return -1;
    }

    return socket_fd;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 84;

    int socket_fd = socket_init(atoi(argv[1]));

    if (socket_fd < 0)
        return 84;

    struct ftp_s *ftp = ftp_init();

    if (ftp == NULL)
        return 84;

    struct poller_s *poller = poller_init(10, socket_fd);

    if (poller == NULL)
        return 84;

    ftp->poller = poller;
    ftp->control_fd = socket_fd;

    while (true) {
        int poll_result = poll(poller->fds, poller->amount, -1);

        if (poll_result == -1) {
            perror("poll");
            return 84;
        }

        poller_handler(ftp);
    };

    return 0;
}
