#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv)
{
    if (argc != 3)
        return 84;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        perror("socket");
        return 84;
    }

    struct sockaddr_in address;
    address.sin_addr.s_addr = inet_addr(argv[1]);
    address.sin_port = htons(atoi(argv[2]));
    address.sin_family = AF_INET;

    int connect_fd = connect(socket_fd, (const struct sockaddr *)&address, sizeof(address));

    if (connect_fd < 0) {
        perror("connect");
        return 84;
    }

    char buffer[BUFFER_SIZE];
    memset(&buffer, 0, BUFFER_SIZE);

    ssize_t bytes_read = read(socket_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("read");
        return 84;
    }
    buffer[bytes_read] = 0;

    printf("Server said: %s", buffer);

    close(connect_fd);
    close(socket_fd);

    return 0;
}
