#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    struct sockaddr_in serv_addr;
    int sock = 0;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n 소켓 생성 실패 \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n지원하지 않는 주소 \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n연결 실패(서버가 닫혀 있다.) \n");
        return -1;
    }
    while(1) {
        printf("보낼 메시지 : ");
        fgets(buffer, 1024, stdin);
        send(sock, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        read(sock, buffer, 1024);
        printf("서버 : %s\n", buffer);
    }

    return 0;
}
