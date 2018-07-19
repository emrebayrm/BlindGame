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
    cout << game <<endl;
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
    game = (BlindGame*)(arg);
    int winner = -1;
    cout << game <<endl;
    while((winner = game->isFinished()) == -1){
        cout << "---" << endl;
        vector<pair<int,int>> dists = game->getCoinDistances();
        cout << "000" << endl;
        sendGameInfos(game, dists);
        cout << "111" << endl;
        while(!game->isTurnFinished()) {
            cout << "222" << endl;
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
    cout << game->isFinished() <<  "sadsa" <<endl;
    pthread_create(&id,NULL,gameRunner,game);
    return true;
}


