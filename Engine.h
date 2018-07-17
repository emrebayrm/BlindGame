//
// Created by patates on 7/16/18.
//
#include <vector>
#include <iostream>
#include "Game.h"
#include "NetworkModule.h"
#include "blindGame.hpp"

#ifndef BLINDGAME_ENGINE_H
#define BLINDGAME_ENGINE_H

using namespace std;


class Engine {
protected:
    NetworkModule *networkModule;

private:

public:
    virtual struct Command doHandshake() = 0;
};


class GameServerEngine : public Engine {
private:
    vector<Game *> gamelist;
    int uid = 0;
    const static int portNumber = 1550;

    struct Command doHandshake();

    bool listGame();

    bool joinGame(int gameid, char *playerName);

    Game *createGame(int maxPlayer, string gameName);

    bool observeGame(int gameid);



public:
    GameServerEngine() {
        networkModule = new ServerNetworkModule();
        networkModule->init(portNumber);
    }

    bool startServer();

    virtual Game *gameObjCreator(int id, int maxPlayer, string gameName) = 0;

};

class BlindGameServerEngine : public GameServerEngine {
    Game *gameObjCreator(int id, int maxPlayer, string gameName) {
        return new BlindGame(id,maxPlayer,gameName);
    }
};

/*
void *gameManger(void* g){
    Game *game;
    game = (Game*) g;
}
*/
#endif //BLINDGAME_ENGINE_H
