//
// Created by patates on 7/16/18.
//

#include "Engine.h"

bool GameServerEngine::startServer() {
    while(1){
        struct Command command;
        listGame();
        command = doHandshake();

        if(command.commandType == CREATE){
            cout << "Create" <<endl;
            createGame();
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

Game *GameServerEngine::createGame() {
    Game *game;
    uid++;
    char *name = new char[10];

    sprintf(name,"game_%d",uid);
    game = new Game(uid,0,name);

    gamelist.push_back(game);

}

bool GameServerEngine::observeGame(int gameid) {
    return false;
}

BlindGame::BlindGame(int id, int a, char *n) : Game(id, a, n) {}
