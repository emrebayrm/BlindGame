//
// Created by patates on 7/17/18.
//

#include "DummyGameServerEngine.h"
#include "DummyGame.h"
#include "../packets.hpp"

Command * DummyGameServerEngine::doHandshake() {
    Command *command = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameJoinCommand_t) + sizeof(GameCreateCommand_t)));
    int ret;
    cout << "Listing Game " << endl;
    listGames();// sending game lists here
    cout << "Receiving operation" << endl;
    ret = networkModule->recvData(command, sizeof(Command));
    cout << "Received operation" << endl;

    if(ret != command->length){
        cout << "something wrong with received data";
    }
//    command->context = malloc(command->length);
   // networkModule->recvData(command->context,command->length);

    return command;
}

Game *DummyGameServerEngine::createGame(GameCreateCommand_t createPacket, GameJoinCommand_t joinPacket) {
    Game *game;

    cout << "requested options are : " << createPacket.maxPlayer << " : " <<
         createPacket.gameName << " : " << sizeof(BlindGame) << endl;
    game = new DummyGame(generateUniqueId(), createPacket.maxPlayer, createPacket.gameName);

    startGameIntoThread(game);
    insertNewGame(game);

    joinPacket.gameId = game->getId();
    joinGame(joinPacket);

    return game;
}


//list game last -1