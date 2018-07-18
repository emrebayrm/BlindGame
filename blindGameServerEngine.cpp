//
// Created by patates on 7/17/18.
//

#include "blindGameServerEngine.hpp"
#include "packets.hpp"

Command * BlindGameServerEngine::doHandshake() {
    Command *command = static_cast<Command *>(malloc(MAX_PAYLOAD));
    int ret;

    listGames();// sending game lists here
    ret = networkModule->recvData(command, MAX_PAYLOAD);

    if(ret != command->length){
        cout << "something wrong with received data";
    }

    return command;
}

//TODO: implement dummy game
Game *BlindGameServerEngine::createGame(GameCreateCommand_t createPacket, GameJoinCommand_t joinPacket) {
    Game *game;

    cout << "requested options are : " << createPacket.maxPlayer << " : " <<
         createPacket.gameName << " : " << endl;
    game = new BlindGame(generateUniqueId(), createPacket.maxPlayer, createPacket.gameName);

    startGameIntoThread(game);
    insertNewGame(game);

    joinPacket.gameId = game->getId();
    joinGame(joinPacket);

    return game;
}
