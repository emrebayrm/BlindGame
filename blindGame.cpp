//
//  blindGame.cpp
//  BlindGame
//
//  Created by Sincap on 16.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#include "blindGame.hpp"

#include <iostream>
#include <string>
#include "player.hpp"

using namespace std;

#define UP 0;
#define RIGHT 1;
#define DOWN 2;
#define LEFT 3;

BlindGame::BlindGame(int id, int maxPlayer, string name) {
    this->maxPlayer = maxPlayer;
    this->currPlayers = 0;
    this->name = name;
    this->id = id;
    this->mapRow = calculateMapRow(maxPlayer);
    this->mapCol = calculateMapCol(maxPlayer);
    this->coinLocation = NULL;
    createMap(mapRow, mapCol);
}

int BlindGame::join(string playerName) {
    if(currPlayers == maxPlayer)
        return -1;
    int playerId = findPlayerId();
    Player *player = new Player(playerId, playerName);
    players[playerId] = player;
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
        it = idSet.find(i);
        if(it == idSet.end()) {
            playerId = i;
            idSet.insert(i);
            break;
        }
    }
    return playerId;
}

bool BlindGame::movePlayer(Player *player, int dir) {
    return false;
}

bool BlindGame::checkBounds(Point p) {
    if(p.getX() < 0 || p.getY() < 0 || p.getX() >= mapRow || p.getY() >= mapCol)
        return false;
    return true;
}

bool BlindGame::isValidPoint(Point p) {
    return false;
}

bool* BlindGame::getCoinDirections() {
    bool* dirs = (bool*) malloc(sizeof(bool) * 4);
    memset(dirs, false, 4);
    Point p(coinLocation->getX() - 1, coinLocation->getY());
    if(coinLocation->getX() > 0 && isValidPoint(p))
        dirs[0] = true;
    
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
vector<Player*> BlindGame::getPlayers() {
    return this->players;
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