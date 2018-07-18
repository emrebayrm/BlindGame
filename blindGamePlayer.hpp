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

#define MAX_MOVES 3

class BlindGame;

class BlindGamePlayer : public Player {
protected:
    Point *location;
    static const int maxMove = MAX_MOVES;
    int currMove;
public:
    BlindGamePlayer();
    BlindGamePlayer(int id, string name);
    Point* getLocation();
    string toString();
    
    //increments currMove by 1.
    void incCurrMove();
    
    //sets currMove to 0.
    void resetCurrMove();
    
    //returns true if the player finished her turn.
    bool isDone();
    
    //moves the player in the given direction. Returns true if the player can move, false otherwise
    bool move(int dir, BlindGame* game);
};

#endif /* blindGamePlayer_hpp */
