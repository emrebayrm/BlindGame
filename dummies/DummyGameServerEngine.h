//
// Created by patates on 7/17/18.
//

#ifndef BLINDGAME_DUMMYGAMESERVERENGINE_H
#define BLINDGAME_DUMMYGAMESERVERENGINE_H


#include "../engine.hpp"
#include "DummyNetworkModule.h"

class DummyGameServerEngine : public GameServerEngine {
public:
    DummyGameServerEngine(){
        networkModule = new DummyNetworkModule();
    }

    Command *doHandshake() override;

    Game *createGame(GameCreateCommand_t command) override;

};


#endif //BLINDGAME_DUMMYGAMESERVERENGINE_H
