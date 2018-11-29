//
//  blindGamePlayer.cpp
//  BlindGame
//
//  Created by Sincap on 17.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#include "blindGamePlayer.hpp"

BlindGamePlayer::BlindGamePlayer(int id, string name) : Player(id, name) {
    this->location = NULL;
    resetCurrMove();
}

bool BlindGamePlayer::isDone() {
    return getCurrMove() == maxMove;
}

int BlindGamePlayer::getCurrMove() {
    return currMove;
}

void BlindGamePlayer::incCurrMove() {
    ++currMove;
}

void BlindGamePlayer::resetCurrMove() {
    currMove = 0;
}

Point* BlindGamePlayer::getLocation() {
    return location;
}

void BlindGamePlayer::setLocation(Point *location) {
    this->location = location;
}

string BlindGamePlayer::toString() {
    return "blindGame";
}
