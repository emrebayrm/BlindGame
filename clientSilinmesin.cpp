//
// Created by patates on 7/16/18.
//
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "networkModule.hpp"
#include "packets.hpp"
#include "mqttHandler.h"

using  namespace std;

int calculateMapRow(int maxPlayer) {
        return 11 + (maxPlayer - 2) * 2;
    }
    
    int calculateMapCol(int maxPlayer) {
        return 11 + (maxPlayer - 2) * 2;
    }

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
    char *temp;
    if()
    cout << "Game List End " << endl;
    
   
    // Create Packet Send
    
    
    int commandChoice;
    cout << "enter createCommand: ";
    cin >> commandChoice;
    GameCreateCommand_t *createPacket;
    GameJoinCommand_t *joinPacket;
    Command *createCommand;
    int maxPlayer;
    switch (commandChoice) {
        case CREATE:
            createCommand = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameJoinCommand_t) + sizeof(GameCreateCommand_t)));
            createCommand->commandType = CREATE;
            createCommand->length =sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t);
            cout << "...." << createCommand->length << endl;
            createPacket = reinterpret_cast<GameCreateCommand_t *>(createCommand->context);
            joinPacket = reinterpret_cast<GameJoinCommand_t *>(createCommand->context + sizeof(GameCreateCommand_t));
            cout << "enter game name: ";
            cin >> createPacket->gameName;
            cout << "enter max player: ";
            cin >> createPacket->maxPlayer;
            maxPlayer = createPacket->maxPlayer;
            cout << "enter player name: ";
            cin >> joinPacket->playerName;
            networkModule.sendData(createCommand,sizeof(Command) + sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t));
            break;
        case JOIN:
            createCommand = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameJoinCommand_t)));
            createCommand->commandType = JOIN;
            joinPacket = reinterpret_cast<GameJoinCommand_t *>(createCommand->context + sizeof(GameCreateCommand_t));
            cout << "enter game id: ";
            cin >> joinPacket->gameId;
            cout << "enter player name: ";
            cin >> joinPacket->playerName;
            networkModule.sendData(createCommand,sizeof(Command) + sizeof(GameJoinCommand_t));
            break;
        case OBSERVE:
            cout << "(o)))" << endl;
            break;
        default:
            break;
    }
    
    Command *topicCommand;
    GameDataCommand_t *topicData;
    topicCommand = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameDataCommand_t)));
    networkModule.recvData(topicCommand,sizeof(Command));
    networkModule.recvData(topicCommand->context,topicCommand->length);
    topicData = reinterpret_cast<GameDataCommand_t *>(topicCommand->context);
    cout << " Topics : "  << topicData->data << endl;
    networkModule.closeConnection();
    
    int cliendId = atoi(strtok(topicData->data, ","));
    int playerId = atoi(strtok(NULL, ","));
    char* posTopic = strtok(NULL, ",");
    char* disTopic = strtok(NULL, ",");
    
    char *sid = (char*) malloc(sizeof(char) * 15);
    sprintf(sid, "PlayerS%d", cliendId);
    
    char *pid = (char*) malloc(sizeof(char) * 15);
    sprintf(pid, "PlayerP%d", cliendId);

    cout << "Pos topic : "<<posTopic << " Dis Topic : " << disTopic <<endl;
    mqttPublisher *positionSender = new mqttPublisher(posTopic, "127.0.0.1", sid);
    mqttSubscriber *distanceCollector = new mqttSubscriber(disTopic, "127.0.0.1", pid);
    
    positionSender->init();
    distanceCollector->init();
    
    int winner = -1;
    

    cout << "Game Starting " << endl;

    while(1){

    }
    
    
    return 0;
    
}
