//
// Created by patates on 7/17/18.
//

#include "blindGameServerEngine.hpp"
#include "packets.hpp"
#include "dummies/DummyGame.h"

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
void *gameRunner(void *arg){
    BlindGame *game;
    game = static_cast<BlindGame *>(arg);
    while(game->isFinished()){

    }
}

bool BlindGameServerEngine::startGameIntoThread(Game *game) {
    GameServerEngine::startGameIntoThread(game);
    pthread_t id;
    //pthread_create(&id,NULL,gameRunner,game);
    return true;
}


