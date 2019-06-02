// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    //char *hello = "Hello from client"; //보내는 스트링 -> 필요없음
    char buffer[1024] = {0};  //스트링 받을 버퍼
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) //소켓 생성
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    //서버 기본설정
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.0.8", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    //서버 접속 요청
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    //메세지 송수신
    //send(sock , hello , strlen(hello) , 0 );
    //printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}
