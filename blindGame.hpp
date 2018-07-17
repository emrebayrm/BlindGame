//
//  blindGame.hpp
//  BlindGame
//
//  Created by Sincap on 16.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#ifndef blindGame_hpp
#define blindGame_hpp

#define EMPTY 'Y'
#define PLAYER 'P'
#define OBSTICLE 'X'
#define COIN 'C'

#include <stdio.h>

#include <string>
#include <vector>
#include <set>

#include "player.hpp"
#include "game.hpp"
#include "point.hpp"

using namespace std;

class BlindGame : public Game {
private:
    char **map;
    int mapRow;
    int mapCol;
    Point *coinLocation;
    
    int calculateMapRow(int maxPlayer);
    int calculateMapCol(int maxPlayer);
    char **createMap(int mapRow, int mapCol);
    int findPlayerId();
    bool checkBounds(Point *p);
    bool isValidPoint(Point *p);
    bool isValidMovement(int dir, Point *p);
    bool* getCoinDirections();
    void playCoin();
    
public:
    BlindGame(int id, int maxPlayer, string name);
    vector<pair<int, int>> getCoinDistances();
    int join(string playerName);    
    
    //getters
    char** getMap();
    int getMaxPlayer();
    int getCurrPlayers();
    Point* getCoinLocation();
    int getId();
    string getName();
    //setters
    void setCurrPlayers(int currPlayers);
};


#endif /* blindGame_hpp */
