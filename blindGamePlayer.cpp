//
//  blindGamePlayer.cpp
//  BlindGame
//
//  Created by Sincap on 17.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#include "blindGamePlayer.hpp"
#include "blindGame.cpp"

BlindGamePlayer::BlindGamePlayer(int id, string name) : Player(id, name) {
    this->location = NULL;
    resetCurrMove();
}

BlindGamePlayer::BlindGamePlayer(){}

bool BlindGamePlayer::isDone() {
    return currMove == maxMove;
}

void BlindGamePlayer::incCurrMove() {
    ++currMove;
}

void BlindGamePlayer::resetCurrMove() {
    currMove = 0;
}

bool BlindGamePlayer::move(int dir, BlindGame *game) {
    if(isDone())
        return false;
    if(game->isValidMovement(dir, location)) {
        location->go(dir);
        incCurrMove();
        return true;
    }
    return false;
}

Point* BlindGamePlayer::getLocation() {
    return location;
}

string BlindGamePlayer::toString() {
    return "blindGame";
}
