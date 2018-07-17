//
// Created by patates on 7/16/18.
//
#include <vector>
#include <iostream>
#include "game.hpp"
#include "networkModule.hpp"
#include "blindGame.hpp"
#include "packets.hpp"

#ifndef BLINDGAME_ENGINE_H
#define BLINDGAME_ENGINE_H

using namespace std;


class Engine {
protected:
    NetworkModule *networkModule;

private:

public:
    virtual GameCommand_t * doHandshake() = 0;
};


class GameServerEngine : public Engine {
private:
    vector<Game *> gamelist;
    int uid = 0;
    const static int portNumber = 1550;
public:
    int generateUniqueId(){
        return ++uid;
    }
    void insertANewGame(Game * g){
        gamelist.push_back(g);
    }
    bool listGame();

    bool joinGame(int gameid, char *playerName);

    virtual Game *createGame(GameCommand_t *command) = 0;

    bool observeGame(int gameid);

    bool startGameIntoThread(Game *);

    GameServerEngine() {
        networkModule = new ServerNetworkModule();
        networkModule->init(portNumber);
    }

    bool startServer();

    virtual Game *gameObjCreator(int id, int maxPlayer, string gameName) = 0;

};

class BlindGameServerEngine : public GameServerEngine {
public:
    Game *gameObjCreator(int id, int maxPlayer, string gameName) {
        return new BlindGame(id,maxPlayer,gameName);
    }
    GameCommand_t * doHandshake();
    Game *createGame(GameCommand_t *command);
};

/*
void *gameManger(void* g){
    Game *game;
    game = (Game*) g;
}
*/
#endif //BLINDGAME_ENGINE_H
