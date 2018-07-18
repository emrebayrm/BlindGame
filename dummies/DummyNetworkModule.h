//
// Created by patates on 7/17/18.
//

#ifndef BLINDGAME_DUMMYNETWORKMODULE_H
#define BLINDGAME_DUMMYNETWORKMODULE_H

#include "../NetworkModule.hpp"
#include "../packets.hpp"
#include <iostream>
#include <cstring>

using namespace std;

class DummyNetworkModule : public ServerNetworkModule{
public:
    Command *command;
    void init(int port) override {
        command = (Command*) malloc(MAX_PAYLOAD);
    }

    int sendData(void *buf, int size) override {
        Command *cmd;
        cmd = static_cast<Command *>(buf);
        if(cmd->commandType == DATA){
            if(cmd->length == 20){
                cout <<  (*(int *) cmd->context) << endl;
            }else
                cout << (const char*)cmd->context << endl;
        }
        return 0;
    }

    int recvData(void *buf, int size) override {
        Command *temp;
        temp = static_cast<Command *>(buf);
        *temp = *command;
        return 0;
    }

    void listenClient() override {
        int type;
        cout << "Enter Command Here " << endl
             << "0 : Create " << endl
             << "1 : Join" << endl
             << "2 : observe " <<endl;
        cin >> type;
        if(type == 0){
            GameCreateCommand_t *createCommand = new GameCreateCommand_t;
            cout << "Enter Max Player  : ";
            cin >> createCommand->maxPlayer;
            cout << "Enter Game Name :";
            cin >> createCommand->gameName;
            command->commandType = CREATE;
            command->length = sizeof(GameCreateCommand_t);
            //command->context = createCommand;
        }
        if(type == 1){
            GameJoinCommand_t *joinCommand = new GameJoinCommand_t;
            cout << "Enter id  ";
            cin >> joinCommand->gameId;
            cout << "Enter Player Name";
            cin >> joinCommand->playerName;
            command->commandType = JOIN;
            command->length = sizeof(GameJoinCommand_t);
            memcpy(command->context, joinCommand , command->length);

        }
        if(type == 2){
            GameObserveCommand_t *observeCommand = new GameObserveCommand_t;
            cout << "Enter id  ";
            cin >> observeCommand->gameId;
            command->commandType = OBSERVE;
            command->length = sizeof(GameObserveCommand_t);

            memcpy(command->context,observeCommand,command->length);
        }

        return;
    }

};


#endif //BLINDGAME_DUMMYNETWORKMODULE_H
