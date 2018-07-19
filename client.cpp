//
// Created by patates on 7/16/18.
//
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "networkModule.hpp"
#include "packets.hpp"

using  namespace std;

int main(int argc, char *argv[]){
    ClientNetworkModule networkModule;
    Command *command;
    GameDataCommand_t *dataCommand;

    command = static_cast<Command *>(malloc(sizeof(Command) ));
    dataCommand = static_cast<GameDataCommand_t *>(malloc(sizeof(GameDataCommand_t)));
    networkModule.init(1550, "127.0.0.1");

    networkModule.recvData(command,sizeof(Command));

    cout << "Game List Start " << endl;

        networkModule.recvData(dataCommand, command->length);

        cout << dataCommand->data << endl;

    cout << "Game List End " << endl;

    // Create Packet Send
    Command *createComand;
    GameCreateCommand_t *createPacket;
    GameJoinCommand_t *joinPacket;

    createComand = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t)));

    createComand->commandType = CREATE;
    createComand->length =sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t);
    cout << "...." << createComand->length << endl;

    createPacket = reinterpret_cast<GameCreateCommand_t *>(createComand->context);
    joinPacket = reinterpret_cast<GameJoinCommand_t *>(createComand->context + sizeof(GameCreateCommand_t));

    sprintf(createPacket->gameName,"Emre's Game");
    createPacket->maxPlayer = 9;

    joinPacket->gameId = -1;
    sprintf(joinPacket->playerName,"Mustafa");
    networkModule.sendData(createComand,sizeof(Command) + sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t));

    // Join Packet Send
    Command *joinComand;

    //Receive topic names
    Command *topicCommand;
    GameDataCommand_t *topicData;

    topicCommand = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameDataCommand_t)));

    networkModule.recvData(topicCommand,sizeof(Command));
    networkModule.recvData(topicCommand->context,topicCommand->length);

    topicData = reinterpret_cast<GameDataCommand_t *>(topicCommand->context);

    cout << " Topics : "  << topicData->data << endl;

    networkModule.closeConnection();

    //2. Client

    ClientNetworkModule networkModule2;
    networkModule2.init(1550, "127.0.0.1");

    cout << "asd" <<endl;
    networkModule2.recvData(command,sizeof(Command));

    cout << "Game List Start " << endl;

    cout << "command length "  << command->length << endl;
    networkModule2.recvData(dataCommand, command->length);
    cout << dataCommand->data << endl;

    cout << "Game List End " << endl;

    // Join Packet Send
    joinComand = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameJoinCommand_t)));

    memset(joinComand,0,sizeof(Command) + sizeof(GameJoinCommand_t));

    joinComand->commandType = JOIN;
    joinComand->length =sizeof(GameJoinCommand_t);

    joinPacket = reinterpret_cast<GameJoinCommand_t *>(joinComand->context);

    joinPacket->gameId = 1;
    sprintf(joinPacket->playerName,"oguz");

    networkModule2.sendData(joinComand,sizeof(Command) + sizeof(GameJoinCommand_t));
    sleep(1);
    networkModule2.closeConnection();

    //Observe
    ClientNetworkModule networkModule3;
    networkModule3.init(1550, "127.0.0.1");

    Command *commandOb;
    GameObserveCommand_t *dataCommandOb;

    commandOb = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameObserveCommand_t)));
    dataCommandOb = reinterpret_cast<GameObserveCommand_t *>(commandOb->context);
    commandOb->commandType = OBSERVE;
    commandOb->length = sizeof(GameObserveCommand_t);
    dataCommandOb->gameId = 1;
    networkModule3.sendData(commandOb,sizeof(Command) + commandOb->length);

    return 0;

}
