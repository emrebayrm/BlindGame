//
// Created by patates on 7/16/18.
//

#include <cstring>
#include "blindGame.hpp"
#include "networkModule.hpp"
#include "engine.hpp"
#include "packets.hpp"

bool GameServerEngine::startServer(int debug) {
    this->debug = debug;
    while (1) {
        GameCommand_t *command;
        ((ServerNetworkModule *) networkModule)->listenClient();
        command = doHandshake();

        if (command->command.commandType == CREATE) {
            cout << "Create" << endl;
            createGame(command);
        } else if (command->command.commandType == JOIN) {
            cout << "Join" << endl;
            joinGame(command->gameId,command->name);
        } else if (command->command.commandType == OBSERVE) {
            cout << "Observe" << endl;
            observeGame(command->gameId);
        }
    }
    return true;
}

bool GameServerEngine::listGames() {
    Command *buffer;
    buffer = (Command *)(malloc(sizeof(Command) + MAX_PAYLOAD));

    for (int i = 0; i < gamelist.size(); ++i) {
        memset(buffer,0,MAX_PAYLOAD);
        buffer->commandType = DATA;
        buffer->length = gamelist[i]->toString().size() + sizeof(Command);

        memcpy(buffer->context, (void *)gamelist[i]->toString().c_str(),gamelist[i]->toString().size());

        networkModule->sendData(buffer, buffer->length);
    }
    free(buffer);
    return true;
}

bool GameServerEngine::joinGame(int gameid, char *playerName) {
    int pid;
    Command *command;
    command = (Command *)(malloc(sizeof(Command) + MAX_PAYLOAD));

    for (int i = 0; i < gamelist.size(); ++i) {
        if (gamelist[i]->getId() == gameid) {
            memset(command,0,MAX_PAYLOAD);
            pid = gamelist[i]->join(playerName);
            memcpy(command->context,&pid, sizeof(pid));
            command->commandType = DATA;
            command->length = sizeof(Command) + sizeof(pid) ;
            networkModule->sendData(&command,command->length);
        }
    }
    return false;
}


bool GameServerEngine::observeGame(int gameid) {
    //
    return false;
}

bool GameServerEngine::startGameIntoThread(Game *game) {
    cout << "Game Object Starting " << endl;
    return true;
}

