//
//  blindGamePlayer.hpp
//  BlindGame
//
//  Created by Sincap on 17.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#ifndef blindGamePlayer_hpp
#define blindGamePlayer_hpp

#include "player.hpp"
#include "point.hpp"
#include "blindGame.hpp"

#define MAX_MOVES 2

class BlindGame;

class BlindGamePlayer : public Player {
private:
    Point* location;
    int currMove;
public:
    static const int maxMove = MAX_MOVES;
    BlindGamePlayer(int id, string name);
    Point* getLocation();
    void setLocation(Point *location);
    string toString();
    int getCurrMove();
    //increments currMove by 1.
    void incCurrMove();
    
    //sets currMove to 0.
    void resetCurrMove();
    
    //returns true if the player finished her turn.
    bool isDone();
    
};

#endif /* blindGamePlayer_hpp */
