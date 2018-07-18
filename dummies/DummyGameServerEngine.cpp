//
// Created by patates on 7/17/18.
//

#include "DummyGameServerEngine.h"
#include "DummyGame.h"
#include "../packets.hpp"

Command * DummyGameServerEngine::doHandshake() {
    Command *command = static_cast<Command *>(malloc(MAX_PAYLOAD));
    int ret;

    listGames();// sending game lists here
    ret = networkModule->recvData(command, MAX_PAYLOAD);

    if(ret != command->length){
        cout << "something wrong with received data";
    }

    return command;
}

Game *DummyGameServerEngine::createGame(GameCreateCommand_t createPacket, GameJoinCommand_t joinPacket) {
    Game *game;
    cout << "requested options are : " << createPacket.maxPlayer << " : " <<
         createPacket.gameName << " : " << endl;

    game = new DummyGame(generateUniqueId(), createPacket.maxPlayer, createPacket.gameName);

    startGameIntoThread(game);
    insertNewGame(game);

    joinGame(joinPacket);

    return game;
}


//list game last -1