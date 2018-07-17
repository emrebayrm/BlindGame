//
// Created by patates on 7/17/18.
//

#include "engine.hpp"
#include "packets.hpp"
#include "blindGameServerEngine.hpp"

int main(){
    BlindGameServerEngine gameServerEngine;
    //DummyNetworkModule *testNetworkModule = new DummyNetworkModule();
    //gameServerEngine.setNetworkModule(testNetworkModule);
    gameServerEngine.startServer();
}