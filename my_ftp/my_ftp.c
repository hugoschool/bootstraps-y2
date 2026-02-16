#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2)
        return 84;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        perror("socket");
        return 84;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(socket_fd);
        return 84;
    }

    if (listen(socket_fd, 1) < 0) {
        perror("listen");
        return 84;
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int accepted_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &client_addr_len);

    if (accepted_fd < 0) {
        perror("accept");
        return 84;
    }

    printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    const char *str = "I lost the game :3\n";
    write(accepted_fd, str, strlen(str));

    close(accepted_fd);
    close(socket_fd);

    return 0;
}
