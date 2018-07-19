//
// Created by patates on 7/17/18.
//

#include "engine.hpp"
#include "packets.hpp"
#include "dummies/DummyNetworkModule.h"
#include "dummies/DummyGameServerEngine.h"

int main(){
    DummyGameServerEngine gameServerEngine;
    DummyNetworkModule *testNetworkModule = new DummyNetworkModule();
    testNetworkModule->init(55, nullptr);
    gameServerEngine.setNetworkModule(testNetworkModule);
    gameServerEngine.startServer();
}