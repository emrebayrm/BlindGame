//
// Created by patates on 7/17/18.
//

#include "networkModule.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <error.h>
#include <memory.h>

#define MAX_LISTEN 20
void ServerNetworkModule::init(int port, char *address) {
    struct sockaddr_in serverAddr;
    socklen_t serverlen;
    int fdSocket=-1;
    // clear server adress
    memset(&serverAddr,0,sizeof(struct sockaddr_in));

    if((fdSocket = socket(AF_INET,SOCK_STREAM,0))<0){
        perror("Socket initialize : ");
        setFd(-1);
    }
    int enable = 1;
    if (setsockopt(fdSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    // IPv4
    serverAddr.sin_family = AF_INET;
    // all local ip addresses
    // convert ip address number to network bytes
    serverAddr.sin_addr.s_addr=htonl(INADDR_ANY); // host to network long integer
    // initialize port number
    // convert short integer port num to network bytes
    serverAddr.sin_port = htons(port);// host to network short integer

    serverlen = sizeof(struct sockaddr_in);

    if(bind(fdSocket,(struct sockaddr*)&serverAddr,serverlen)<0){
        perror("Binding socket : ");
        setFd(-1);
    }

    // listen socket comming connetions
    if(listen(fdSocket,MAX_LISTEN)){
        perror("Listen socket : ");
        setFd(-1);
    }

    setFd(fdSocket);

}

int ServerNetworkModule::sendData(void *buf, int size) {
    if(currentClientFd<0){
	printf("Send Error!");
    	return 0;
	}

    int readed = 0;
    while ( readed < size) {
        readed += send(currentClientFd, buf+readed, size-readed, 0);
    }
    return readed;
}

int ServerNetworkModule::recvData(void *buf, int size) {
    if(currentClientFd<0){
	printf("Receive Error!");
    	return 0;
	}
	int readed = 0;
	while ( readed < size) {
        readed += recv(currentClientFd, buf+readed, size-readed, 0);
	}
    return readed;
}

void ServerNetworkModule::listenClient() {
    struct sockaddr_in clientAddr; // client socket informations
    socklen_t clientAddrLen; // client socket address length

    // initialize size of struct
    clientAddrLen = sizeof(struct sockaddr_in);
    if(getFd()<0) {
	perror("Initialize socket");
	return;}
    //clear junk values
    memset(&clientAddr,0,clientAddrLen);
    currentClientFd = accept(getFd(),(struct sockaddr*)&clientAddr,&clientAddrLen);
}

void ClientNetworkModule::init(int port, char *address) {
  int sockfd = 0,n = 0;
  struct sockaddr_in serv_addr;
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
      printf("\n Error : Could not create socket \n");
      return ;
    }
 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = inet_addr(address);
 
  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
      printf("\n Error : Connect Failed \n");
      return ;
    }
    setFd(sockfd);
}

int ClientNetworkModule::sendData(void *buf, int size) {
    if(fd<0){
		printf("Send Error!");
    	return -1;
	}
    int readed = 0;
    while ( readed < size) {
        readed += send(fd, buf+readed, size-readed, 0);
    }
    return readed;
}



int ClientNetworkModule::recvData(void *buf, int size) {
    if(fd<0){
		printf("Receive Error!");
    	return -1;
	}
    int readed = 0;
    while ( readed < size) {
        readed += recv(fd, buf+readed, size-readed, 0);
        if(readed <= 0)
            perror("asd");

    }
    return readed;
}