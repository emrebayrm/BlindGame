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

using namespace std;
#define DEBUG 1

int calculateMapRow(int maxPlayer) {
    return 11 + (maxPlayer - 2) * 2;
}

int calculateMapCol(int maxPlayer) {
    return 11 + (maxPlayer - 2) * 2;
}

void printMap(int row, int col, int x, int y, int coinDist);

int main(int argc, char *argv[]) {
    ClientNetworkModule networkModule;
    Command *command;
    GameDataCommand_t *dataCommand;

    command = static_cast<Command *>(malloc(sizeof(Command)));
    dataCommand = static_cast<GameDataCommand_t *>(malloc(sizeof(GameDataCommand_t)));
    char addres[] = "127.0.0.1";
    networkModule.init(1550, addres);

    networkModule.recvData(command, sizeof(Command));

    cout << "Game List Start " << endl;

    networkModule.recvData(dataCommand, command->length);

    cout << dataCommand->data << endl;
    char *temp;
    cout << "Game List End " << endl;


    // Create Packet Send

    int commandChoice;
    cout << "enter createCommand: ";
    cin >> commandChoice;

    GameCreateCommand_t *createPacket;
    GameJoinCommand_t *joinPacket;
    Command *createCommand;
    int maxPlayer;
    int gid = -1;

    switch (commandChoice) {
        case CREATE:
            createCommand = static_cast<Command *>(malloc(
                    sizeof(Command) + sizeof(GameJoinCommand_t) + sizeof(GameCreateCommand_t)));
            createCommand->commandType = CREATE;
            createCommand->length = sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t);
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
            networkModule.sendData(createCommand,
                                   sizeof(Command) + sizeof(GameCreateCommand_t) + sizeof(GameJoinCommand_t));
            break;
        case JOIN:
            createCommand = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameJoinCommand_t)));
            createCommand->commandType = JOIN;
            joinPacket = reinterpret_cast<GameJoinCommand_t *>(createCommand->context + sizeof(GameCreateCommand_t));
            cout << "enter game id: ";
            cin >> joinPacket->gameId;
            cout << "enter player name: ";
            cin >> joinPacket->playerName;

            if (command->length != 0) {
                temp = strtok(dataCommand->data, ":/\n ");
                while (temp != NULL) {
                    temp = strtok(NULL, ":/\n ");
                    temp = strtok(NULL, ":/\n ");
                    gid = atoi(temp);
                    temp = strtok(NULL, ":/\n ");
                    temp = strtok(NULL, ":/\n ");
                    temp = strtok(NULL, ":/\n ");
                    temp = strtok(NULL, ":/\n ");
                    temp = strtok(NULL, ":/\n ");
                    maxPlayer = atoi(temp);
#ifdef DEBUG
                    cout << "Parsed " << gid << "   " << maxPlayer << endl;
#endif
                    if (gid == joinPacket->gameId) {
                        break;
                    }
                }
            }

            networkModule.sendData(createCommand, sizeof(Command) + sizeof(GameJoinCommand_t));
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
    networkModule.recvData(topicCommand, sizeof(Command));
    networkModule.recvData(topicCommand->context, topicCommand->length);
    topicData = reinterpret_cast<GameDataCommand_t *>(topicCommand->context);
    cout << " Topics : " << topicData->data << endl;
    networkModule.closeConnection();

    int cliendId = atoi(strtok(topicData->data, ","));
    int playerId = atoi(strtok(NULL, ","));
    char *disTopic = strtok(NULL, ",");
    char *posTopic = strtok(NULL, ",");

    char *sid = (char *) malloc(sizeof(char) * 15);
    sprintf(sid, "PlayerS%d", cliendId);

    char *pid = (char *) malloc(sizeof(char) * 15);
    sprintf(pid, "PlayerP%d", cliendId);

    cout << "Pos topic : " << posTopic << " Dis Topic : " << disTopic << endl;
    mqttPublisher *positionSender = new mqttPublisher(posTopic, "127.0.0.1", sid);
    mqttSubscriber *distanceCollector = new mqttSubscriber(disTopic, "127.0.0.1", pid);

    positionSender->init();
    distanceCollector->init();

    int winner = -1;


    cout << "Game Starting " << endl;
    int col, row, x, y;
    col = calculateMapCol(maxPlayer);
    row = calculateMapRow(maxPlayer);
    x = ((col + 1) / 2);
    y = ((row + 1) / 2);
    string buffer;
    char *receivedPacket;
    int tmppid;
    int flag;
    int curMove;
    int distance;
    receivedPacket = static_cast<char *>(calloc(sizeof(char) , 200));

    while (1) {
        memset(receivedPacket,0,200);
        cout << "-- : " <<  distanceCollector->receive(receivedPacket) << endl;
        //flag,pid,currMove,X,Y,dist-pid,currMove,X,Y,dist-....

        if ((temp = strtok(receivedPacket, ",-")) != NULL)
            flag = atoi(temp);
        cout << receivedPacket << endl;
        while (temp != NULL) {
            temp = strtok(NULL, ",-");
            tmppid = atoi(temp);
            temp = strtok(NULL, ",-");
            curMove = atoi(temp);
            temp = strtok(NULL, ",-");
            x = atoi(temp);
            temp = strtok(NULL, ",-");
            y = atoi(temp);
            temp = strtok(NULL, ",-");
            distance = atoi(temp);
            if (tmppid == playerId) {
                break;
            }
        }
        //printMap(row, col, x, y, distance);
        while(curMove < 3) {
            cout << "X: " << x << "  Y: " << y << "  Dist: " << distance << "   CurrMove: " << curMove << endl;
            int inp;
            cout << "Enter direction 0: Up 1:Right 2:Down 3:Left " << endl;
            cin >> inp;
            buffer.clear();
            buffer.append(to_string(playerId));
            buffer.append(",");
            buffer.append(to_string(inp));
            positionSender->publish(buffer);
            curMove++;
        }
    }


    return 0;

}

void printMap(int row, int col, int x, int y, int coinDist) {
    for (int i = 0; i < col; ++i)
        cout << "-";
    cout << endl;
    for (int i = 0; i < col; ++i) {
        cout << "| ";
        for (int j = 0; j < row; ++j) {
            if (i == y && j == x) {
                cout << 'X';
            } else if ((x - coinDist > i && y - coinDist > j) || (x + coinDist > i && y + coinDist > i))
                cout << ".";
            else
                cout << " ";
        }
        cout << " |" << endl;
    }
    for (int i = 0; i < col; ++i)
        cout << "-";
    cout << endl;

}