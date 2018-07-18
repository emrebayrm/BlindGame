//
// Created by patates on 7/17/18.
//

#include "blindGameServerEngine.hpp"
#include "packets.hpp"

Command * BlindGameServerEngine::doHandshake() {
    Command *command = static_cast<Command *>(malloc(sizeof(Command)));
    int ret;
    cout << "Listing Game " << endl;
    listGames();// sending game lists here
    cout << "Receiving operation" << endl;
    networkModule->recvData(command, sizeof(Command));
    cout << "Received operation" << endl;

    if(ret != command->length){
        cout << "something wrong with received data";
    }
    networkModule->recvData(command->context,command->length);
    return command;
}


Game *BlindGameServerEngine::createGame(GameCreateCommand_t createPacket, GameJoinCommand_t joinPacket) {
    Game *game;

    cout << "requested options are : " << createPacket.maxPlayer << " : " <<
         createPacket.gameName << " : " << sizeof(BlindGame) << endl;
    game = new BlindGame(generateUniqueId(), createPacket.maxPlayer, createPacket.gameName);

    startGameIntoThread(game);
    insertNewGame(game);

    joinPacket.gameId = game->getId();
    joinGame(joinPacket);

    return game;
}
