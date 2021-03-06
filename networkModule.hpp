//
// Created by patates on 7/17/18.
//

#ifndef BLINDGAME_NETWORKMODULE_H
#define BLINDGAME_NETWORKMODULE_H

#include <unistd.h>
#define MAX_PAYLOAD 1400


class NetworkModule{
private:
    int fd=-1;
    int port;
public:
    virtual void init(int port, char *address) = 0;
    virtual int sendData(void *buf, int size) = 0;
    virtual int recvData(void *buf, int size) = 0;
    int getFd(){ return fd;}
    int getPort(){ return port;}
    void setFd(int _fd){ fd=_fd;}

};

class ServerNetworkModule : public NetworkModule{
private:
    int currentClientFd=-1;
public:
    void init(int port, char *address);
    int sendData(void *buf, int size);
    int recvData(void *buf, int size);

    virtual void listenClient();

};

class ClientNetworkModule : public NetworkModule{
private:
    int fd=-1;
public:
    void init(int port, char *address);
    int sendData(void *buf, int size);
    int recvData(void *buf, int size);
    void setFd(int _fd){ fd=_fd;}
    void closeConnection(){
        close(getFd());
    }
};


#endif //BLINDGAME_NETWORKMODULE_H
