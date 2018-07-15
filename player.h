//
//  player.h
//  BlindGame
//
//  Created by Sincap on 14.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#ifndef player_h
#define player_h

#include <stdio.h>
#include "point.h"

typedef struct {
    int playerID;
    Point *location;
    char name[10];
} Player;

#endif /* player_h */
