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
    cout << "Server Started " << endl;
    while (1) {
        Command *command;

        ((ServerNetworkModule *) networkModule)->listenClient();
        cout << "Client Connected" <<endl;
        command = doHandshake();
        cout << "Handshake completed" <<endl;

        if (command->commandType == CREATE) {
            cout << "Create" << endl;
            int ret = 0;
            GameCreateCommand_t *createCommand;
            createCommand = new GameCreateCommand_t;
            ret += networkModule->recvData(createCommand,sizeof(GameCreateCommand_t));
            GameJoinCommand_t *joinCommand;
            joinCommand = new GameJoinCommand_t;
            ret += networkModule->recvData(joinCommand, sizeof(GameJoinCommand_t));
            if(ret != command->length){
                cout << "Something Wrong in Create" << endl;
            }
            createGame(*createCommand, *joinCommand);

        } else if (command->commandType == JOIN) {
            cout << "Join" << endl;
            GameJoinCommand_t *joinCommand;
            joinCommand = new GameJoinCommand_t;
            networkModule->recvData(joinCommand,command->length);

            joinGame(*joinCommand);
        } else if (command->commandType == OBSERVE) {
            cout << "Observe" << endl;
            GameObserveCommand_t *observeCommand;
            observeCommand = new GameObserveCommand_t;

            networkModule->recvData(observeCommand,command->length);
            observeGame(*observeCommand);
        }
    }
    return true;
}

bool GameServerEngine::listGames() {
    Command *buffer;
    GameDataCommand_t *dataCommand;
    buffer = (Command *)(malloc(sizeof(Command) + sizeof(GameDataCommand_t)));
    dataCommand = reinterpret_cast<GameDataCommand_t *>(buffer->context);
    memset(dataCommand,0,sizeof(GameDataCommand_t));
    buffer->commandType = DATA;
    int i;
    for (i = 0; i < gamelist.size(); ++i) {
        strcat(dataCommand->data,gamelist[i]->toString().c_str());
        strcat(dataCommand->data,"\n");
    }
    if (i > 0)
        buffer->length = strlen(dataCommand->data);
    else
        buffer->length = 0;
    cout << "sended data" << dataCommand->data << endl;

    networkModule->sendData(buffer,buffer->length + sizeof(Command));
    return true;
}
bool GameServerEngine::joinGame(GameJoinCommand_t command) {
    int pid;
    GameDataCommand_t *dataCommand;
    Command *sentTopic;
    static int unqid = 0;
    for (int i = 0; i < gamelist.size(); ++i) {
        if (gamelist[i]->getId() == command.gameId) {

            pid = gamelist[i]->join(command.playerName);

            sentTopic = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameDataCommand_t)));

            sentTopic->commandType = DATA;
            dataCommand = reinterpret_cast<GameDataCommand_t *>(sentTopic->context);
            sentTopic->length = sprintf(dataCommand->data, "%d,%d,pos%d,dis%d",unqid,pid , command.gameId, command.gameId);
            ++unqid;
            networkModule->sendData(sentTopic, sizeof(Command) + sentTopic->length);

            free(sentTopic);
        }
    }

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

