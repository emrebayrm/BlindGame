//
// Created by patates on 7/17/18.
//

#ifndef BLINDGAME_BLINDGAMESERVERENGINE_H
#define BLINDGAME_BLINDGAMESERVERENGINE_H

#include "packets.hpp"
#include "game.hpp"
#include "engine.hpp"

class BlindGameServerEngine : public GameServerEngine {
public:
    Command * doHandshake();
    Game *createGame(GameCreateCommand_t createPacket, GameJoinCommand_t joinPacket);
};


#endif //BLINDGAME_BLINDGAMESERVERENGINE_H
