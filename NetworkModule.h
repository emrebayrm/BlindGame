//
// Created by patates on 7/17/18.
//

#ifndef BLINDGAME_NETWORKMODULE_H
#define BLINDGAME_NETWORKMODULE_H


typedef enum {CREATE, JOIN, OBSERVE} command_type;

struct Command{
    command_type commandType;
    int length;
    void* context;
};


class NetworkModule{
private:
    int fd;
    int port;
public:
    virtual void init(int port) = 0;
    virtual int send(void *buf, int size) = 0;
    virtual int recv(void *buf, int size) = 0;
    int getFd(){ return fd;}
    int getPort(){ return port;}

};

class ServerNetworkModule : public NetworkModule{
    void init(int port);
    int send(void *buf, int size);
    int recv(void *buf, int size);
    void listen();
    
};

class ClientNetworkModule : public NetworkModule{
    void init(int port);
    int send(void *buf, int size);
    int recv(void *buf, int size);
};


#endif //BLINDGAME_NETWORKMODULE_H
