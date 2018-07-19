//
// Created by patates on 7/17/18.
//

#include "blindGameServerEngine.hpp"
#include "packets.hpp"
#include "dummies/DummyGame.h"
#include "blindGamePlayer.hpp"
#include <vector>
#include <cstring>


Command * BlindGameServerEngine::doHandshake() {
    Command *command = static_cast<Command *>(malloc(sizeof(Command)));
    int ret;
    cout << "Listing Game " << endl;
    listGames();// sending game lists here
    cout << "Receiving operation" << endl;
    ret = networkModule->recvData(command, sizeof(Command));
    cout << "Received operation" << endl;

    if(ret != command->length){
        cout << "something wrong with received data";
    }
//    networkModule->recvData(command->context,command->length);
    return command;
}


Game *BlindGameServerEngine::createGame(GameCreateCommand_t createPacket, GameJoinCommand_t joinPacket) {
    BlindGame *game;

    cout << "requested options are : " << createPacket.maxPlayer << " : " <<
         createPacket.gameName << " : " << sizeof(BlindGame) << endl;
    game = new BlindGame(generateUniqueId(), createPacket.maxPlayer, createPacket.gameName);

    insertNewGame(game);

    joinPacket.gameId = game->getId();
    joinGame(joinPacket);
    cout << game <<endl;
    string pos,dis;
    pos.append("pos");
    pos.append(to_string(game->getId()));
    dis.append("dis");
    dis.append(to_string(game->getId()));
    game->setTopicNames(dis,pos);
    startGameIntoThread(game);

    return game;
}

void sendGameInfos(BlindGame *game, vector<pair<int,int>> dists) {
    char *distPack;
    distPack = (char*) calloc(sizeof(char), game->getCurrPlayers() * 12 * sizeof(char) + 4);

    strcat(distPack,to_string(game->isFinished()).c_str());
    strcat(distPack,",");
    //flag,pid,currMove,X,Y,dist-.....
    for(int i = 0; i < dists.size(); ++i) {
        pair<int,int> p = dists[i];
        BlindGamePlayer *player = (BlindGamePlayer*) game->getPlayer(p.first);
        strcat(distPack,to_string(p.first).c_str());
        strcat(distPack,",");
        strcat(distPack, to_string(player->getCurrMove()).c_str());
        strcat(distPack,",");
        strcat(distPack, to_string(player->getLocation()->getX()).c_str());
        strcat(distPack,",");
        strcat(distPack, to_string(player->getLocation()->getY()).c_str());
        strcat(distPack,",");
        strcat(distPack, to_string(p.second).c_str());
        strcat(distPack,"-");
    }

    strcat(distPack, "");
    cout << "DistPack:"<< distPack << endl;
    game->distanceSender->publish(distPack);
}

void *gameRunner(void *arg){
    BlindGame *game;
    game = (BlindGame*)(arg);
    int winner = -1;
    cout << game <<endl;
    game->startGame();
    vector<pair<int,int>> dists = game->getCoinDistances();
    usleep(500000);
    sendGameInfos(game, dists);
    while((winner = game->isFinished()) == -1){
        int x = 3;
        while(x != 0) {
            char *received;
            received = static_cast<char *>(calloc(sizeof(char), 20));
            if(game->positionCollecter->receive(received) != 0) {
                char *playerId;
                int pId;
                char *dir;
                int pDir;
                cout << "received packet from client : " << received << endl;
                playerId = strtok(received, ",");
                pId = atoi(playerId);
                dir = strtok(NULL, ",");
                pDir = atoi(dir);
                game->movePlayer(pDir, pId);
                dists = game->getCoinDistances();
                sendGameInfos(game, dists);
            }
            free(received);
            x--;
        }
    }
}

bool BlindGameServerEngine::startGameIntoThread(Game *game) {
    GameServerEngine::startGameIntoThread(game);
    pthread_t id;

    pthread_create(&id,NULL,gameRunner,game);
    return true;
}


