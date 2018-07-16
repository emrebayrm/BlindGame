//
//  point.cpp
//  BlindGame
//
//  Created by Sincap on 16.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#include "point.hpp"

#include <iostream>

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::getX() {
    return this->x;
}
int Point::getY() {
    return this->y;
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
