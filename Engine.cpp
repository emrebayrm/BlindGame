//
// Created by patates on 7/16/18.
//

#include "Engine.h"
#include "blindGame.hpp"
#include "NetworkModule.h"

bool GameServerEngine::startServer() {
    while(1){
        struct Command command;
        listGame();
        command = doHandshake();

        if(command.commandType == CREATE){
            cout << "Create" <<endl;
            createGame(0, std::__cxx11::string());
        }
        else if(command.commandType == JOIN){
            cout << "Join" <<endl;
            joinGame(1,"emre");
        }
        else if(command.commandType == OBSERVE){
            cout << "Observe" <<endl;
            observeGame(0);
        }
    }
    return true;
}

bool GameServerEngine::listGame() {
    for (int i = 0; i < gamelist.size(); ++i) {
        cout << gamelist[i]->toString() << endl;

    }

}

struct Command GameServerEngine::doHandshake() {
    struct Command command;
    int type;
    cin >> type;
    command.commandType = (command_type)type;
    return command;
}

bool GameServerEngine::joinGame(int gameid, char *playerName) {
    int pid;
    for (int i = 0; i < gamelist.size(); ++i) {
        if(gamelist[i]->getId() == gameid){

            pid = gamelist[i]->join(playerName);
            // networkModule.send();
        }
    }
    return false;
}

Game *GameServerEngine::createGame(int maxPlayer, string gameName) {
    Game *game;
    uid++;
    char *name = new char[10];

    sprintf(name,"game_%d",uid);
    game = new BlindGame(uid,maxPlayer,gameName);
    // getSenderTopicName
    // send
    // getReceiverTopicName
    // send

    gamelist.push_back(game);

}

bool GameServerEngine::observeGame(int gameid) {
    //
    return false;
}