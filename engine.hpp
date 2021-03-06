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
    virtual Command * doHandshake() = 0;
};


class GameServerEngine : public Engine {
private:
    vector<Game *> gamelist;
    int uid = 0;
    const static int portNumber = 1550;
    int debug ;

public:
    int generateUniqueId(){
        return ++uid;
    }
    void insertNewGame(Game *game){
        gamelist.push_back(game);
    }
    bool listGames();

    bool joinGame(GameJoinCommand_t command);

    virtual Game *createGame(GameCreateCommand_t createPacket, GameJoinCommand_t joinPacket) = 0;

    bool observeGame(GameObserveCommand_t observeData);

    bool startGameIntoThread(Game *game);

    GameServerEngine() {
        debug = 0;
        networkModule = new ServerNetworkModule();
        networkModule->init(portNumber, "127.0.0.1");
    }

    void setNetworkModule(NetworkModule * _networkModule){
        this->networkModule = _networkModule;
    }

    bool startServer(int debug = 0);

};


/*
void *gameManger(void* g){
    Game *game;
    game = (Game*) g;
}
*/
#endif //BLINDGAME_ENGINE_H
