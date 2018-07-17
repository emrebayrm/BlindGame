//
// Created by patates on 7/17/18.
//

#include "engine.hpp"

class testNetworkModule : public NetworkModule {
public:
    void init(int port) override {

    }

    int sendData(void *buf, int size) override {
        return 0;
    }

    int recvData(void *buf, int size) override {
        return 0;
    }

public:

};