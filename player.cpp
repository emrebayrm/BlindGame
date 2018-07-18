//
//  player.cpp
//  BlindGame
//
//  Created by Sincap on 16.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#include "player.hpp"

#include <string>

using namespace std;

Player::Player(){}

Player::Player(int id, string name) {
    this->id = id;
    this->name = name;
}

int Player::getId() {
    return this->id;
}

string Player::getName() {
    return this->name;
}
