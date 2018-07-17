//
// Created by patates on 7/16/18.
//

#include "blindGame.hpp"
#include "networkModule.hpp"
#include "engine.hpp"
#include "packets.hpp"

bool GameServerEngine::startServer() {
    while (1) {
        GameCommand_t *command;
        listGame();
        command = doHandshake();

        if (command->command.commandType == CREATE) {
            cout << "Create" << endl;
            createGame(command);
        } else if (command->command.commandType == JOIN) {
            cout << "Join" << endl;
            joinGame(command->gameId,command->name);
        } else if (command->command.commandType == OBSERVE) {
            cout << "Observe" << endl;
            observeGame(command->gameId);
        }
    }
    return true;
}

bool GameServerEngine::listGame() {
    Command buffer;

    for (int i = 0; i < gamelist.size(); ++i) {
        buffer.commandType = DATA;
        buffer.length = gamelist[i]->toString().size() + sizeof(buffer);
        buffer.context = (void *)gamelist[i]->toString().c_str();

        networkModule->send(&buffer, buffer.length);
    }
    return true;
}

bool GameServerEngine::joinGame(int gameid, char *playerName) {
    int pid;
    Command command;
    for (int i = 0; i < gamelist.size(); ++i) {
        if (gamelist[i]->getId() == gameid) {
            pid = gamelist[i]->join(playerName);
            command.context = &pid;
            command.commandType = DATA;
            command.length = sizeof(command);
            networkModule->send(&command,command.length);
        }
    }
    return false;
}

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
    insertANewGame(game);

}

bool GameServerEngine::observeGame(int gameid) {
    //
    return false;
}

bool GameServerEngine::startGameIntoThread(Game *) {
    cout << "Game Object Starting " << endl;
    return true;
}

GameCommand_t * BlindGameServerEngine::doHandshake() {
    GameCommand_t *command = new GameCommand_t;
    int ret;

    listGame();// sending game lists here
    ret = networkModule->recv(&command, sizeof(command));

    if(ret != command->command.length){
        cout << "something wrong with received data";
    }

    return command;
}
