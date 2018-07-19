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

int main(int argc, char *argv[]){
    ClientNetworkModule networkModule;
    Command *command;
    GameDataCommand_t *dataCommand;
    
    command = static_cast<Command *>(malloc(sizeof(Command) ));
    dataCommand = static_cast<GameDataCommand_t *>(malloc(sizeof(GameDataCommand_t)));
    networkModule.init(1550);
    
    networkModule.recvData(command,sizeof(Command));
    
    cout << "Game List Start " << endl;
    
    networkModule.recvData(dataCommand, command->length);
    
    cout << dataCommand->data << endl;
    
    cout << "Game List End " << endl;
    
   
    // Create Packet Send
    
    
    int commandChoice;
    cout << "enter command: ";
    cin >> commandChoice;
    
    int calculateMapRow(int maxPlayer) {
        return 11 + (maxPlayer - 2) * 2;
    }
    
    int calculateMapCol(int maxPlayer) {
        return 11 + (maxPlayer - 2) * 2;
    }
    Command *command;
    switch (commandChoice) {
        case CREATE:
            GameCreateCommand_t *createPacket;
            GameJoinCommand_t *joinPacket;
            command = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameJoinCommand_t) + sizeof(GameCreateCommand_t)));
            command->commandType = CREATE;
            command->length =sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t);
            cout << "...." << command->length << endl;
            createPacket = reinterpret_cast<GameCreateCommand_t *>(command->context);
            joinPacket = reinterpret_cast<GameJoinCommand_t *>(command->context + sizeof(GameCreateCommand_t));
            string name;
            cout << "enter game name: ";
            cin >> createPacket->gameName;
            cout << "enter max player: ";
            cin >> createPacket->maxPlayer;
            cout << "enter player name: ";
            cin >> joinPacket->playerName;
            networkModule.sendData(command,sizeof(Command) + sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t));
            break;
        case JOIN:
            GameJoinCommand_t *joinPacket;
            command = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameJoinCommand_t)));
            command->commandType = JOIN;
            joinPacket = reinterpret_cast<GameJoinCommand_t *>(createComand->context + sizeof(GameCreateCommand_t));
            cout << "enter game id: ";
            cin >> joinPacket->gameId;
            cout << "enter player name: ";
            cin >> joinPacket->playerName;
            networkModule.sendData(command,sizeof(Command) + sizeof(GameJoinCommand_t));
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
    
    mqttPublisher *positionSender = new mqttPublisher(posTopic, "127.0.0.1", sid);
    mqttSubscriber *distanceCollector = new mqttSubscriber(disTopic, "127.0.0.1", pid);
    
    positionSender.init();
    distanceCollector.init();
    
    
    
    return 0;
    
}
