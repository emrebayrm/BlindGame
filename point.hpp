//
//  point.hpp
//  BlindGame
//
//  Created by Sincap on 16.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <stdio.h>

class Point {
private:
    int x;
    int y;
public:
    Point(int x, int y);
    void incX();
    void incY();
    void decX();
    void decY();
    int distance(Point *p);
    //gettters
    int getX();
    int getY();
    //setters
    void setX(int x);
    void setY(int y);
};

#endif /* point_hpp */
