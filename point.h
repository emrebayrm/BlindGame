//
//  point.h
//  BlindGame
//
//  Created by Sincap on 14.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#ifndef point_h
#define point_h

#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

void incX(Point *p);
void incY(Point *p);
void decX(Point *p);
void decY(Point *p);

#endif /* point_h */
