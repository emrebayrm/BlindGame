//
// Created by patates on 7/17/18.
//

#ifndef BLINDGAME_DUMMYNETWORKMODULE_H
#define BLINDGAME_DUMMYNETWORKMODULE_H

#include "../networkModule.hpp"
#include "../packets.hpp"
#include <iostream>
using namespace std;

class DummyNetworkModule : public ServerNetworkModule{
public:
    GameCommand_t command;
    void init(int port) override {

    }

    int sendData(void *buf, int size) override {
        Command *cmd;
        cmd = static_cast<Command *>(buf);
        if(cmd->commandType == DATA){
            cout << cmd->context << endl;
        }
        return 0;
    }

    int recvData(void *buf, int size) override {
        GameCommand_t *temp;
        temp = static_cast<GameCommand_t *>(buf);
        *temp = command;
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
            cout << "Enter Max Player  : ";
            cin >> command.maxPlayer;
            cout << "Enter Game Name :";
            cin >> command.name;
            command.command.commandType = CREATE;
        }
        if(type == 1){
            cout << "Enter id  ";
            cin >> command.gameId;
            command.command.commandType = JOIN;
        }
        if(type == 2){
            cout << "Enter id  ";
            cin >> command.gameId;
            command.command.commandType = OBSERVE;
        }

        return;
    }

};


#endif //BLINDGAME_DUMMYNETWORKMODULE_H
