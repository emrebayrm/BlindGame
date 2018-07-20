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
    char *addres = argv[1];
    networkModule.init(1550, addres);

    networkModule.recvData(command, sizeof(Command));

    cout << "Game List Start " << endl;

    networkModule.recvData(dataCommand, command->length);

    cout << dataCommand->data << endl;
    char *temp;
    cout << "Game List End " << endl;


    // Create Packet Send

    int commandChoice;
    cout << "enter Command: ";
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
            createCommand->length =sizeof(GameJoinCommand_t);
            joinPacket = reinterpret_cast<GameJoinCommand_t *>(createCommand->context);
            cout << "enter game id: ";
            cin >> joinPacket->gameId;
            cout << "enter player name: ";
            cin >> joinPacket->playerName;

            if (command->length != 0) {
                temp = strtok(dataCommand->data, ":/\n ");
                while (temp != NULL) {
                    temp = strtok(NULL, ":/\n ");
                   // temp = strtok(NULL, ":/\n ");
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
    mqttPublisher *positionSender = new mqttPublisher(posTopic, addres, sid);
    mqttSubscriber *distanceCollector = new mqttSubscriber(disTopic, addres, pid);

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
    volatile int flag = -1;
    int curMove ;
    int distance;
    receivedPacket = static_cast<char *>(calloc(sizeof(char) , 200));

    while (flag == -1) {
        memset(receivedPacket,0,200);
        //cout << "-- : " <<  distanceCollector->receive(receivedPacket) << endl;
        distanceCollector->receive(receivedPacket);
        //flag,pid,currMove,X,Y,dist-pid,currMove,X,Y,dist-....
        cout << receivedPacket << endl;
        if ((temp = strtok(receivedPacket, ",")) != NULL)
            flag = atoi(temp);
        if(flag != -1 )
            break;
        while (temp != NULL) {
            temp = strtok(NULL, ",");
            tmppid = atoi(temp);
            temp = strtok(NULL, ",");
            curMove = atoi(temp);
            temp = strtok(NULL, ",");
            x = atoi(temp);
            temp = strtok(NULL, ",");
            y = atoi(temp);
            temp = strtok(NULL, ",-");
            distance = atoi(temp);
            if (tmppid == playerId) {
                break;
            }
        }
        curMove = 0;
        printMap(row, col, x, y, distance);
        while(curMove < 3) {
            cout << "X: " << x << "  Y: " << y << "  Dist: " << distance << "   CurrMove: " << curMove << endl;
            int inp;
            againinput:
            cout << "Enter direction 0: Up 1:Right 2:Down 3:Left " << endl;
            cin >> inp;
            if(inp > 3 || inp < 0) {
                cout << "Invalid Direction !!" <<endl;
                goto againinput;
            }
            buffer.clear();
            buffer.append(to_string(playerId));
            buffer.append(",");
            buffer.append(to_string(inp));
            positionSender->publish(buffer);
            curMove++;
        }
        cout << "Waiting for other player to play "  << endl;
    }

    cout << "Winner " <<flag << endl;

    if(flag == playerId){
        cout << "!!! Congrat " << endl;
    }else
        cout << "You lost :( ... "  << endl;
    return 0;

}

void printMap(int row, int col, int x, int y, int coinDist) {
    printf("r:%d c:%d x:%d y:%d dist:%d\n",row,col,x,y,coinDist);
    printf("  ");
    for (int i = 0; i < col; ++i)
        printf("%2d ",i);
    cout << endl << "  ";
    for (int i = 0; i < col; ++i)
        printf("---");
    cout << "--" << endl;
    for (int i = 0; i < col; ++i) {
        printf("%2d|",i);
        for (int j = 0; j < row; ++j) {
            if (i == y && j == x) {
                cout << " X ";
            }else if( (((i - y)*(i - y)) + ((j - x)*(j - x))) <= (coinDist*coinDist) ){
                cout << "***";
            }
            else
                cout << "   ";
        }
        cout << " |" << endl;
    }
    cout << "  ";
    for (int i = 0; i < col; ++i)
        printf("---");
    cout << "--" << endl;
    printf("  ");
    for (int i = 0; i < col; ++i)
        printf("%2d ",i);
    printf("\n");
}