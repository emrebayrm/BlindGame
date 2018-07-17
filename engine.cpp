//
// Created by patates on 7/16/18.
//

#include <cstring>
#include "blindGame.hpp"
#include "networkModule.hpp"
#include "engine.hpp"
#include "packets.hpp"

bool GameServerEngine::startServer() {
    while (1) {
        GameCommand_t *command;
        ((ServerNetworkModule *) networkModule)->listenClient();
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
    Command *buffer;
    buffer = (Command *)(malloc(sizeof(Command) + MAX_PAYLOAD));

    for (int i = 0; i < gamelist.size(); ++i) {
        memset(buffer,0,MAX_PAYLOAD);
        buffer->commandType = DATA;
        buffer->length = gamelist[i]->toString().size() + sizeof(Command);

        memcpy(buffer->context, (void *)gamelist[i]->toString().c_str(),gamelist[i]->toString().size());

        networkModule->sendData(buffer, buffer->length);
    }
    return true;
}

bool GameServerEngine::joinGame(int gameid, char *playerName) {
    int pid;
    Command *command;
    command = (Command *)(malloc(sizeof(Command) + MAX_PAYLOAD));

    for (int i = 0; i < gamelist.size(); ++i) {
        if (gamelist[i]->getId() == gameid) {
            memset(command,0,MAX_PAYLOAD);
            pid = gamelist[i]->join(playerName);
            memcpy(command->context,&pid, sizeof(pid));
            command->commandType = DATA;
            command->length = sizeof(Command) + sizeof(pid) ;
            networkModule->sendData(&command,command->length);
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

bool GameServerEngine::startGameIntoThread(Game *game) {
    cout << "Game Object Starting " << endl;
    return true;
}

GameCommand_t * BlindGameServerEngine::doHandshake() {
    GameCommand_t *command = new GameCommand_t;
    int ret;

    listGame();// sending game lists here
    ret = networkModule->recvData(&command, sizeof(command));

    if(ret != command->command.length){
        cout << "something wrong with received data";
    }

    return command;
}
