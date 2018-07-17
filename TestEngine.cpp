//
// Created by patates on 7/17/18.
//

#include "engine.hpp"
#include "packets.hpp"
#include "blindGameServerEngine.hpp"

class TestNetworkModule : public ServerNetworkModule{
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

int main(){
    BlindGameServerEngine gameServerEngine;
    //TestNetworkModule *testNetworkModule = new TestNetworkModule();
    //gameServerEngine.setNetworkModule(testNetworkModule);
    gameServerEngine.startServer();
}