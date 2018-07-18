//
// Created by patates on 7/17/18.
//

#ifndef BLINDGAME_NETWORKMODULE_H
#define BLINDGAME_NETWORKMODULE_H

#define MAX_PAYLOAD 200


class networkModule{
private:
    int fd=-1;
    int port;
public:
    virtual void init(int port) = 0;
    virtual int sendData(void *buf, int size) = 0;
    virtual int recvData(void *buf, int size) = 0;
    int getFd(){ return fd;}
    int getPort(){ return port;}
    void setFd(int _fd){ fd=_fd;}

};

class ServerNetworkModule : public networkModule{
private:
    int currentClientFd=-1;
public:
    void init(int port);
    int sendData(void *buf, int size);
    int recvData(void *buf, int size);

    virtual void listenClient();

};

class ClientNetworkModule : public networkModule{
private:
    int fd=-1;
public:
    void init(int port);
    int sendData(void *buf, int size);
    int recvData(void *buf, int size);
    void setFd(int _fd){ fd=_fd;}
};


#endif //BLINDGAME_NETWORKMODULE_H
