//
//  point.cpp
//  BlindGame
//
//  Created by Sincap on 16.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#include <cstdlib>
#include "point.hpp"
#include "blindGame.hpp"

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

void Point::incX() {
    ++this->x;
}
void Point::incY() {
    ++this->y;
}
void Point::decX() {
    --this->x;
}
void Point::decY() {
    --this->y;
}

int Point::distance(Point *p) {
    return abs(this->x - p->x) + abs(this->y - p->y);
}

void Point::go(int dir) {
    if(dir == UP) {
        decX();
    } else if(dir == RIGHT) {
        incY();
    } else if(dir == DOWN) {
        incX();
    } else if(dir == LEFT) {
        decY();
    }
}

//getters
int Point::getX() {
    return this->x;
}
int Point::getY() {
    return this->y;
}
//setters
void Point::setX(int x) {
    this->x = x;
}
void Point::setY(int y) {
    this->y = y;
}
