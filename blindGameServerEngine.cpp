//
// Created by patates on 7/17/18.
//

#include "blindGameServerEngine.hpp"
#include "packets.hpp"

GameCommand_t * BlindGameServerEngine::doHandshake() {
    GameCommand_t *command = new GameCommand_t;
    int ret;

    listGames();// sending game lists here
    ret = networkModule->recvData(command, sizeof(command));

    if(ret != command->command.length){
        cout << "something wrong with received data";
    }

    return command;
}

//TODO: implement dummy game
Game *BlindGameServerEngine::createGame(GameCommand_t *command) {
    Game *game;
    GameCommand_t *blindGameCommand;
    blindGameCommand = command;
    GameCommand_t buffer;

    cout << "requested options are : " << blindGameCommand->maxPlayer << " : " <<
         blindGameCommand->name << " : " << endl;
    game = new BlindGame(generateUniqueId(), blindGameCommand->maxPlayer, blindGameCommand->name);

    // getSenderTopicName
    // send
    // getReceiverTopicName
    // send

    startGameIntoThread(game);
    insertNewGame(game);
    //joinGame(game->getId(),command->name);

}
