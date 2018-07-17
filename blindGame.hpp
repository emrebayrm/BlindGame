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
    
public:
    BlindGame(int id, int maxPlayer, string name);
    bool movePlayer(Player *player, int dir);
    vector<pair<int, int>> getCoinDistances();
    int join(std::string playerName);
    int findPlayerId();
    bool checkBounds(Point p);
    bool isValidPointMovement(Point p);
    bool* getCoinDirections();
    void playCoin();
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
