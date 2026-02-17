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

struct poller_s {
    struct pollfd *fds;

    // current amount of elements in the array
    unsigned int amount;

    // size of the array
    unsigned int size;
};

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

void client_handler(struct poller_s *poller, int i, int socket_fd)
{
    size_t a = 256;
    char buffer[a];
    int fd = poller->fds[i].fd;

    if (read(fd, buffer, a) <= 0) {
        if (fd != socket_fd) {
            if (close(fd) == -1)
                perror("close");
            poller_fd_delete(poller, i);
            i--;
        }
    } else {
        const char *str = "I lost the game :3\n";
        if (write(fd, str, strlen(str)) == -1) {
            perror("write");
        }
    }
}

void poller_handler(struct poller_s *poller, int socket_fd)
{
    unsigned int amount = poller->amount;

    for (unsigned int i = 0; i < amount; i++) {
        if (poller->fds[i].revents & POLLIN) {
            if (poller->fds[i].fd == socket_fd) {
                new_client_handler(poller, socket_fd);
            } else {
                client_handler(poller, i, socket_fd);
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

    struct poller_s *poller = poller_init(10, socket_fd);

    while (true) {
        int poll_result = poll(poller->fds, poller->amount, -1);

        if (poll_result == -1) {
            perror("poll");
            return 84;
        }

        poller_handler(poller, socket_fd);
    };

    return 0;
}
