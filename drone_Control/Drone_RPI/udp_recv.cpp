#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 256

void error_handling(char * msg);

int main(){
  int sock;
  char msg[BUF_SIZE];
  char ip_addr[32] = "192.168.43.151";   //ip 확인 후 변경
  int port_num = 4300;    //port num 확인 후 변경

  int str_len;
  socklen_t adr_sz;
  struct sockaddr_in serv_addr, from_addr;
  /*  ip addr / port number 메인함수 인자로 받아오는 경우 예외처리임.
  if(argc != 3){
    printf("Usage : %s <IP> <port>\n", argv[0]);
    exit(1);
  }
  */
  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sock == -1){
    error_handling("socker() error");
  }
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(ip_addr);
  serv_addr.sin_port = htons(port_num);

  while(1){
    str_len = recvfrom(sock, msg, BUF_SIZE, 0, (struct sockaddr*)&from_addr, &adr_sz);
    msg[str_len] = 0;
    printf("msg from serv : %s\n", msg);
  }
  close(sock);

  return 0;
}

void error_handling(char *msg){
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
