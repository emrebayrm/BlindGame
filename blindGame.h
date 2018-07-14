//
//  blindGame.h
//  BlindGame
//
//  Created by Sincap on 14.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#ifndef blindGame_h
#define blindGame_h

#include <stdio.h>
#include "point.h"
#include "player.h"

typedef struct {
    char **map;
    int maxPlayer;
    int currPlayers;
    Point goalPoint;
    Player *players;
    int id;
} BlindGame;

int isValidDir(Point *p, int dir, char **map);

void moveChar(Player *player, int dir, char **map);



#endif /* blindGame_h */
