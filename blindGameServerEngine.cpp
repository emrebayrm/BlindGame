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
    Game *game;

    cout << "requested options are : " << createPacket.maxPlayer << " : " <<
         createPacket.gameName << " : " << sizeof(BlindGame) << endl;
    game = new BlindGame(generateUniqueId(), createPacket.maxPlayer, createPacket.gameName);

    insertNewGame(game);

    joinPacket.gameId = game->getId();
    joinGame(joinPacket);

    startGameIntoThread(game);

    return game;
}

void sendGameInfos(BlindGame *game, vector<pair<int,int>> dists) {
    char *distPack = (char*) malloc(game->getCurrPlayers() * 12 * sizeof(char) + 1);
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
    game->distanceSender->publish(distPack);
}

void *gameRunner(void *arg){
    BlindGame *game;
    game = static_cast<BlindGame *>(arg);
    int winner = -1;
    while((winner = game->isFinished()) == -1){
        vector<pair<int,int>> dists = game->getCoinDistances();
        sendGameInfos(game, dists);
        while(!game->isTurnFinished()) {
            char *received;
            if(game->positionCollecter->receive(received) != 0) {
                char *playerId = strtok(received, ",");
                int pId = atoi(playerId);
                char *dir = strtok(NULL, ",");
                int pDir = atoi(dir);
                game->movePlayer(pDir, pId);
                sendGameInfos(game, dists);
            }
        }
    }
}

bool BlindGameServerEngine::startGameIntoThread(Game *game) {
    GameServerEngine::startGameIntoThread(game);
    pthread_t id;
    //pthread_create(&id,NULL,gameRunner,game);
    return true;
}


