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

    command = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameDataCommand_t)));

    networkModule.init(1550);

    networkModule.recvData(command,sizeof(Command) + sizeof(GameDataCommand_t));

    cout << "Game List Start " << endl;
    while (command->length != -1){
        dataCommand = reinterpret_cast<GameDataCommand_t *>(command->context);

        cout << dataCommand->data << endl;

        networkModule.recvData(command,sizeof(Command) + sizeof(GameDataCommand_t));
    }
    cout << "Game List End " << endl;

    // Create Packet Send
    Command *createComand;
    GameCreateCommand_t *createPacket;
    GameJoinCommand_t *joinPacket;

    createComand = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t)));

    createComand->commandType = CREATE;
    createComand->length =sizeof(GameCreateCommand_t);

    createPacket = reinterpret_cast<GameCreateCommand_t *>(createComand->context);
    joinPacket = reinterpret_cast<GameJoinCommand_t *>(createComand->context + sizeof(GameCreateCommand_t));

    sprintf(createPacket->gameName,"Emre's Game");
    createPacket->maxPlayer = 9;

    joinPacket->gameId = -1;
    sprintf(joinPacket->playerName,"Mustafa");

    networkModule.sendData(createComand,sizeof(Command) + sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t));

    // Join Packet Send
    Command *joinComand;
/*    GameJoinCommand_t *joinPacket;

    joinComand = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameJoinCommand_t)));

    joinComand->commandType = JOIN;
    joinComand->length =sizeof(GameJoinCommand_t);

    joinPacket = reinterpret_cast<GameJoinCommand_t *>(joinComand->context);

    joinPacket->gameId = -1;
    sprintf(joinPacket->playerName,"Mustafa");

    NetworkModule.sendData(joinComand,sizeof(Command) + sizeof(GameJoinCommand_t));
*/

    //Receive topic names
    Command *topicCommand;
    GameDataCommand_t *topicData;

    topicCommand = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameDataCommand_t)));

    networkModule.recvData(topicCommand,sizeof(Command) + sizeof(GameDataCommand_t));

    topicData = reinterpret_cast<GameDataCommand_t *>(topicCommand->context);

    cout << " Topics : "  << topicData->data << endl;

    networkModule.closeConnection();

    //2. Client

    ClientNetworkModule networkModule2;
    networkModule2.init(1550);


    networkModule2.recvData(command,sizeof(Command) + sizeof(GameDataCommand_t));

    cout << "Game List Start " << endl;
    while (command->length != -1){
        dataCommand = reinterpret_cast<GameDataCommand_t *>(command->context);

        cout << dataCommand->data << endl;

        networkModule2.recvData(command,sizeof(Command) + sizeof(GameDataCommand_t));
    }
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
    networkModule2.closeConnection();


}
