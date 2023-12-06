#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_http_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

    char method[10], path[100];
    sscanf(buffer, "%s %s", method, path);

    if (strcmp(method, "GET") == 0) {
    }
    else if (strcmp(method, "POST") == 0) {
    }
    if (strcmp(method, "POST") == 0) {
    char *headers_end = strstr(buffer, "\r\n\r\n");
    if (headers_end) {
        char *body = headers_end + 4;

        printf("POST : %s\n", body);
    }
}
    if (strcmp(path, "/cgi-bin/script") == 0) {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execl("/path/to/cgi-bin/script", "script", NULL);
        exit(1);
    } else {
        close(fd[1]);
        char cgi_output[1024];
        read(fd[0], cgi_output, sizeof(cgi_output));

        send(client_socket, cgi_output, strlen(cgi_output), 0);
    }

}

    char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTEST...";
    send(client_socket, response, strlen(response), 0);

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        handle_http_request(new_socket);
    }

    return 0;
}
