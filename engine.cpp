//
// Created by patates on 7/16/18.
//

#include <cstring>
#include "blindGame.hpp"
#include "networkModule.hpp"
#include "engine.hpp"
#include "packets.hpp"
//TODO: debug level
bool GameServerEngine::startServer(int debug) {
    this->debug = debug;
    while (1) {
        Command *command;
        if(debug == 1)
            listGames();
        ((ServerNetworkModule *) networkModule)->listenClient();
        command = doHandshake();

        if (command->commandType == CREATE) {
            cout << "Create" << endl;

            GameCreateCommand_t *createCommand;
            createCommand = static_cast<GameCreateCommand_t *>(command->context);

            createGame(*createCommand);

        } else if (command->commandType == JOIN) {
            cout << "Join" << endl;
            GameJoinCommand_t joinCommand;

            memcpy(&joinCommand,command->context,command->length);

            joinGame(joinCommand);
        } else if (command->commandType == OBSERVE) {
            cout << "Observe" << endl;
            GameObserveCommand_t observeCommand;

            memcpy(&observeCommand,command->context,command->length);

            observeGame(observeCommand);
        }
    }
    return true;
}

bool GameServerEngine::listGames() {
    Command *buffer;
    GameDataCommand_t *dataCommand;
    buffer = (Command *)(malloc(sizeof(Command)));
    void *address;
    for (int i = 0; i < gamelist.size(); ++i) {
        buffer->commandType = DATA;
        buffer->length = gamelist[i]->toString().size();
        dataCommand = static_cast<GameDataCommand_t *>(malloc(gamelist[i]->toString().size()));

        buffer->context = dataCommand;
        /*
        char *tmp = static_cast<char *>(buffer->context);
        for (int j = 0; j < gamelist[i]->toString().size(); ++j) {
            tmp[j] = gamelist[i]->toString().c_str()[j];
        }
        buffer->context = address;
        */
        memcpy(dataCommand->data, (void *)(gamelist[i]->toString().c_str()),gamelist[i]->toString().size());
        //buffer->context = (void *)gamelist[i]->toString().c_str();
        networkModule->sendData(buffer, buffer->length);
    }
    free(buffer);
    return true;
}

bool GameServerEngine::joinGame(GameJoinCommand_t command) {
    int *pid = new int;
    Command command_sent;
    GameDataCommand_t *dataCommand;
    dataCommand = (GameDataCommand_t *)(malloc(sizeof(int)));

    for (int i = 0; i < gamelist.size(); ++i) {
        if (gamelist[i]->getId() == command.gameId) {

            *pid = gamelist[i]->join(command.playerName);

            memcpy(dataCommand->data,pid, sizeof(int));
            //*(int *)dataCommand->data = pid;
            command_sent.commandType = DATA;
            command_sent.length = sizeof(Command) + sizeof(int) ;
            command_sent.context = dataCommand;
            networkModule->sendData(&command_sent, command_sent.length);
        }
    }
    delete(pid);
    free(dataCommand);
    return false;
}


bool GameServerEngine::observeGame(GameObserveCommand_t observeData) {
    //sendTopicinfo
    for (int i = 0; i < gamelist.size(); ++i) {
        if(observeData.gameId = gamelist[i]->getId()){
            for (int j = 0; j < gamelist[i]->getPlayers().size(); ++j) {
                cout <<  gamelist[i]->getPlayers()[j]->toString() << endl;
            }
        }
    }
    cout << endl;
    return false;
}

bool GameServerEngine::startGameIntoThread(Game *game) {
    cout << "Game Object Starting "  <<  endl;
    return true;
}

