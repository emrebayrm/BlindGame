//
// Created by patates on 7/16/18.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include "ServerNetworkModule.h"

int connectServer(const char *ipnum, int portnum){
    int fd;
    struct sockaddr_in serverAddr;
    socklen_t serverArrLen;

    if((fd=socket(AF_INET,SOCK_STREAM,0))<0){
        return -1;
    }

    serverArrLen = sizeof(struct sockaddr_in);
    memset(&serverAddr,0,serverArrLen);
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=inet_addr(ipnum);
    serverAddr.sin_port=htons(portnum);

    if(connect(fd,(struct sockaddr*)&serverAddr,serverArrLen)<0){
        return -1;
    }

    return fd;
}

int main(int argc, char *argv[]){
    int fd;
    game_info_t gm;
    Command_t cm;
    fd = connectServer("127.0.0.1",1550);
    while(recv(fd,&gm, sizeof(game_info_t),0) > 0){
        if(gm.maxplayer == -1)
            break;
        printf("%d   %s   %d/%d    %d,%d \n",gm.gameid,gm.game_name,gm.Connected_players,gm.maxplayer,gm.mapCol,gm.mapRow);

    }
    printf("Received \n");
    cm.gameid = gm.gameid;
    cm.req = CREATE;
    sprintf(cm.playerName,"Emre");
    cm.maxPlayer = 7;
    sprintf(cm.gameName,"Game 1");
    printf("sending command \n");
    send(fd,&cm, sizeof(cm),0);
    Command_response_t res;

    recv(fd,&res,sizeof(res),0);

    printf("%d    %s    %s \n",res.playerid,res.distance_tpc,res.position_tpc);
    close(fd);
    return 0;
}
