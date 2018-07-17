//
//  blindGame.cpp
//  BlindGame
//
//  Created by Sincap on 16.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#include "blindGame.hpp"

#include <string>
#include <cstring>
#include "blindGamePlayer.hpp"

using namespace std;

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

BlindGame::BlindGame(int id, int maxPlayer, string name) : Game(id, maxPlayer, name) {
    this->mapRow = calculateMapRow(maxPlayer);
    this->mapCol = calculateMapCol(maxPlayer);
    this->coinLocation = NULL;
    createMap(mapRow, mapCol);
}

int BlindGame::join(string playerName) {
    if(currPlayers == maxPlayer)
        return -1;
    int playerId;
    playerId = findPlayerId();
    Player *player = new BlindGamePlayer(playerId, playerName);
    getPlayers()[playerId] = player;
    return playerId;
}

int BlindGame::calculateMapRow(int maxPlayer) {
    return 10 + (maxPlayer - 2) * 2;
}

int BlindGame::calculateMapCol(int maxPlayer) {
    return 10 + (maxPlayer - 2) * 2;
}

char** BlindGame::createMap(int mapRow, int mapCol) {
    char **map = (char**) malloc(sizeof(char*) * mapRow);
    for(int i = 0; i < mapRow; ++i)
        map[i] = (char*) malloc(sizeof(char) * mapCol);
    for(int i = 0; i < mapRow; ++i) {
        memset(map[i], 'Y', mapCol);
    }
    return map;
}

int BlindGame::findPlayerId() {
    int playerId = -1;
    for(int i = 0; i < maxPlayer; ++i) {
        set<int>::iterator it;
        it = playerIdSet.find(i);
        if(it == playerIdSet.end()) {
            playerId = i;
            playerIdSet.insert(i);
            break;
        }
    }
    return playerId;
}


bool BlindGame::checkBounds(Point *p) {
    if(p->getX() < 0 || p->getY() < 0 || p->getX() >= mapRow || p->getY() >= mapCol)
        return false;
    return true;
}

bool BlindGame::isValidPoint(Point *p) {
    if(!checkBounds(p))
        return false;
    if(map[p->getX()][p->getY()] == OBSTICLE)
        return false;
    return true;
}

bool BlindGame::isValidMovement(int dir, Point *p) {
    Point *point;
    if(dir == UP) {
        point = new Point(p->getX() + 1, p->getY());
    } else if(dir == RIGHT) {
        point = new Point(p->getX(), p->getY() + 1);
    } else if(dir == DOWN) {
        point = new Point(p->getX() - 1, p->getY());
    } else if(dir == LEFT) {
        point = new Point(p->getX(), p->getY() - 1);
    } else
        return false;
    if(!isValidPoint(point))
        return false;
    return true;
}

bool* BlindGame::getCoinDirections() {
    bool* dirs = (bool*) malloc(sizeof(bool) * 4);
    memset(dirs, false, 4);
    
    if(isValidMovement(UP, coinLocation))
        dirs[UP] = true;
    if(isValidMovement(RIGHT, coinLocation))
        dirs[RIGHT] = true;
    if(isValidMovement(DOWN, coinLocation))
        dirs[DOWN] = true;
    if(isValidMovement(LEFT, coinLocation))
        dirs[LEFT] = true;
    return dirs;
}

void BlindGame::playCoin() {
    
}

//getters
char** BlindGame::getMap() {
    return this->map;
}
int BlindGame::getMaxPlayer() {
    return this->maxPlayer;
}
int BlindGame::getCurrPlayers() {
    return this->currPlayers;
}
Point* BlindGame::getCoinLocation() {
    return this->coinLocation;
}

int BlindGame::getId() {
    return this->id;
}
string BlindGame::getName() {
    return this->name;
}
//setters
void BlindGame::setCurrPlayers(int currPlayers) {
    if(currPlayers > maxPlayer)
        return;
    this->currPlayers = currPlayers;
}
