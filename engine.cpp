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
            createCommand = reinterpret_cast<GameCreateCommand_t *>(command->context);
            GameJoinCommand_t *joinCommand;
            joinCommand = reinterpret_cast<GameJoinCommand_t *>(command->context + sizeof(GameCreateCommand_t));

            createGame(*createCommand, *joinCommand);

        } else if (command->commandType == JOIN) {
            cout << "Join" << endl;
            GameJoinCommand_t *joinCommand;
            joinCommand = reinterpret_cast<GameJoinCommand_t *>(command->context);

            joinGame(*joinCommand);
        } else if (command->commandType == OBSERVE) {
            cout << "Observe" << endl;
            GameObserveCommand_t *observeCommand;
            observeCommand = reinterpret_cast<GameObserveCommand_t *>(command->context);

            observeGame(*observeCommand);
        }
    }
    return true;
}

bool GameServerEngine::listGames() {
    Command *buffer;
    GameDataCommand_t *dataCommand;
    buffer = (Command *)(malloc(sizeof(Command) + sizeof(GameDataCommand_t)));

    buffer->commandType = DATA;
    for (int i = 0; i < gamelist.size(); ++i) {

        buffer->length = gamelist[i]->toString().size();

        dataCommand = reinterpret_cast<GameDataCommand_t *>(buffer->context);

        sprintf(dataCommand->data,"%s",gamelist[i]->toString().c_str());

        networkModule->sendData(buffer, buffer->length);
    }

    buffer->length = -1;
    networkModule->sendData(buffer, sizeof(Command));

    free(buffer);
    return true;
}

bool GameServerEngine::joinGame(GameJoinCommand_t command) {
    int *pid = new int;
    GameDataCommand_t *dataCommand;
    Command *sentTopic;

    for (int i = 0; i < gamelist.size(); ++i) {
        if (gamelist[i]->getId() == command.gameId) {

            *pid = gamelist[i]->join(command.playerName);

            sentTopic = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameDataCommand_t)));

            sentTopic->commandType = DATA;
            dataCommand = reinterpret_cast<GameDataCommand_t *>(sentTopic->context);
            sentTopic->length = sprintf(dataCommand->data,"pos_%d , dis_%d",command.gameId,command.gameId);

            networkModule->sendData(sentTopic,sizeof(Command) + sizeof(GameDataCommand_t));

        }
    }
    delete(pid);
//    free(sentTopic);
    return false;
}


bool GameServerEngine::observeGame(GameObserveCommand_t observeData) {
    //sendTopicinfo
    GameDataCommand_t *dataCommand;
    Command *sentTopic;

    for (int i = 0; i < gamelist.size(); ++i) {
        if(observeData.gameId = gamelist[i]->getId()){

            sentTopic = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameDataCommand_t)));

            sentTopic->commandType = DATA;
            dataCommand = reinterpret_cast<GameDataCommand_t *>(sentTopic->context);
            sentTopic->length = sprintf(dataCommand->data,"pos_%d , dis_%d",observeData.gameId,observeData.gameId);

            networkModule->sendData(sentTopic,sizeof(Command) + sizeof(GameDataCommand_t));

        }
    }

    return false;
}

bool GameServerEngine::startGameIntoThread(Game *game) {
    cout << "Game Object Starting "  <<  endl;
    return true;
}

