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
#include "point.hpp"

#include <iostream>

using namespace std;

BlindGame::BlindGame(int id, int maxPlayer, string name) : Game(id, maxPlayer, name) {
    this->mapRow = calculateMapRow(maxPlayer);
    this->mapCol = calculateMapCol(maxPlayer);
    srand(time(NULL));
}

void BlindGame::resetMoves() {
    for(int i = 0; i < players.size(); ++i) {
        BlindGamePlayer *player = (BlindGamePlayer*) players[i];
        player->resetCurrMove();
    }
}

int BlindGame::join(string playerName) {
    if(currPlayers == maxPlayer)
        return -1;
    int playerId;
    playerId = findPlayerId();
    Player *player = new BlindGamePlayer(playerId, playerName);
    players[playerId] = player;
    ++currPlayers;
    return playerId;
}

int BlindGame::calculateMapRow(int maxPlayer) {
    return 11 + (maxPlayer - 2) * 2;
}

int BlindGame::calculateMapCol(int maxPlayer) {
    return 11 + (maxPlayer - 2) * 2;
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

bool BlindGame::movePlayer(int dir, int playerId) {
    BlindGamePlayer *player = (BlindGamePlayer*) players[playerId];
        if(player->isDone())
            return false;
        if(isValidMovement(dir, player->getLocation())) {
            player->getLocation()->go(dir);
            player->incCurrMove();
            if(isTurnFinished()) {
                playCoin(2);
            }
            return true;
        }
        return false;
}

bool BlindGame::isTurnFinished() {
    for(int i = 0; i < currPlayers; ++i) {
        BlindGamePlayer *player = (BlindGamePlayer*) players[i];
        if(player->getCurrMove() != player->maxMove)
            return false;
    }
    resetMoves();
    return true;
}


bool BlindGame::checkBounds(Point *p) {
    if(p->getX() < 0 || p->getY() < 0 || p->getX() >= mapRow || p->getY() >= mapCol)
        return false;
    return true;
}

bool BlindGame::isValidPoint(Point *p) {
    if(!checkBounds(p))
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
    } else {
        delete point;
        return false;
    }
    if(!isValidPoint(point)) {
       delete point;
        return false;
    }
    delete point;
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

int BlindGame::isFinished() {
    for(int i = 0; i < getPlayers().size(); ++i) {
        BlindGamePlayer *p = (BlindGamePlayer*) getPlayers()[i];
        if(p->getLocation()->getX() == coinLocation->getX() && p->getLocation()->getY() == coinLocation->getY())
            return p->getId();
    }
    return -1;
}

Point* BlindGame::getRandomCoinPoint() {
    int row = rand() % mapRow;
    int col = rand() % mapCol;

    return new Point(row, col);
}

void BlindGame::placeCoin() {
    coinLocation = getRandomCoinPoint();
}

void BlindGame::placePlayers() {
    for(int i = 0; i < currPlayers; ++i) {
        ((BlindGamePlayer*)(players[i]))->setLocation(new Point(mapRow / 2, mapCol / 2));
    }
}

void BlindGame::startGame() {
    string pubid;
    pubid.append("serverP");
    pubid.append(to_string(getId()));

    string subid;
    subid.append("serverS");
    subid.append(to_string(getId()));

    distanceSender = new mqttPublisher(distanceTopic,address,pubid);
    positionCollecter = new mqttSubscriber(positionTopic,address,subid);
    distanceSender->init();
    positionCollecter->init();
    placePlayers();
    placeCoin();
}

vector<pair<int,int>> BlindGame::getCoinDistances() {
    vector<pair<int,int>> dists;
    for(int i = 0; i < players.size(); ++i) {
        BlindGamePlayer *player = (BlindGamePlayer*) players[i];
        pair<int, int> p;
        p.first = player->getId();
        p.second = player->getLocation()->distance(coinLocation);
        dists.push_back(p);
    }
    return dists;
}

//getters
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
