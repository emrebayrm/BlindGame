#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define PAYLOAD_MAX 200
typedef enum {CREATE, JOIN, OBSERVE} command_type;

struct Command{
    command_type commandType;
    int length;
    char context[0];
};
 
int main(void)
{
  int sockfd = 0,n = 0;
  char recvBuff[1024];
  struct sockaddr_in serv_addr;
  struct Command *cmd;
  cmd = malloc(PAYLOAD_MAX);
  memset(cmd, 0 ,PAYLOAD_MAX);
  memset(recvBuff, '0' ,sizeof(recvBuff));
  char *ptr;
  int i;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
      printf("\n Error : Could not create socket \n");
      return 1;
    }
 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5000);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
      printf("\n Error : Connect Failed \n");
      return 1;
    }
 
  if((n = recv(sockfd, cmd, 24,0)) > 0)
    {
	
      ptr=cmd->context;

      for(i=0;i<8;i++){
        printf("%c",ptr[i]);
	
	}
      printf("\n");
    }
    
  else
    {

      perror("\n Read Error \n");
    }
  cmd->context[0]='1';
  send(sockfd,cmd,24,0);
  close(sockfd);
  return 0;
}
