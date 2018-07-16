//
//  player.hpp
//  BlindGame
//
//  Created by Sincap on 16.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>

#include <string>
#include "point.hpp"

#define MAX_MOVES 3;

using namespace std;

class Player {
private:
    int id;
    string name;
    Point *location;
    int currMove;
public:
    Player(int id, string name);
    const static int maxMoves = MAX_MOVES;
    int getId();
    string getName();
    Point* getLocation();
    int getCurrMove();
};

#endif /* player_hpp */
