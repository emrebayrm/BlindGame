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
#include "goal.h"

typedef struct {
    char **map;
    int mapRow;
    int mapCol;
    int maxPlayer;
    int currPlayers;
    char blocks[5];
    Goal *goal;
    Player *players;
    int gameID;
} BlindGame;

void moveObject(BlindGame *game, int dir, void *movable, void (*moveOp) (void*));

void movePlayer(BlindGame *game, int dir, Player *player);
void moveGoal(BlindGame *game, int dir, Goal *goal);

//returns 0 if the point is out of bounds, 1 otherwise
int checkBounds(BlindGame *game, Point p);

//returns 0 if the point is invalid, 1 otherwise
int isValidPoint(BlindGame *game, Point p);

//generates the map
void generateMap(BlindGame *game);

//finds a random valid location in the map
Point* getRandomPoint(BlindGame *game);

//places the goal
void placeGoal(BlindGame *game);

//returns 0 if the game is not finished, playerID otherwise
int isFinished(BlindGame *game);




#endif /* blindGame_h */
