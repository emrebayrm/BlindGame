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
#include <time.h>

using namespace std;

BlindGame::BlindGame(int id, int maxPlayer, string name) : Game(id, maxPlayer, name) {
    this->mapRow = calculateMapRow(maxPlayer);
    this->mapCol = calculateMapCol(maxPlayer);
    createMap(mapRow, mapCol);
    srand(time(NULL));
}

int BlindGame::join(string playerName) {
    if(currPlayers == maxPlayer)
        return -1;
    int playerId;
    playerId = findPlayerId();
    Player *player = new BlindGamePlayer(playerId, playerName);
    getPlayers()[playerId] = player;
    setCurrPlayers(getCurrPlayers() + 1);
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

vector<int> BlindGame::getCoinDirections() {
    vector<int> dirs;
    for(int i = 0; i < 4; ++i)
        if(isValidMovement(i, coinLocation))
            dirs.push_back(i);
    return dirs;
}

void BlindGame::playCoin(int moveC) {
    for(int i = 0; i < moveC; ++i) {
        vector<int> dirs = getCoinDirections();
        if(dirs.size() == 0)
            return;
        int dir = rand() % dirs.size();
        moveCoin(dir);
    }
}

void BlindGame::moveCoin(int dir) {
    if(dir == UP)
        coinLocation->go(UP);
    else if(dir == RIGHT)
        coinLocation->go(RIGHT);
    else if(dir == DOWN)
        coinLocation->go(DOWN);
    else if(dir == LEFT)
        coinLocation->go(LEFT);
}

bool BlindGame::isFinished() {
    for(int i = 0; i < getPlayers().size(); ++i) {
        BlindGamePlayer *p = (BlindGamePlayer*) getPlayers()[i];
        if(p->getLocation()->getX() == coinLocation->getX() && p->getLocation()->getY() == coinLocation->getY())
            return true;
    }
    return true;
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
    return coinLocation;
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
