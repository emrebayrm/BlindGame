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

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#include <string>
#include <vector>
#include <set>

#include "player.hpp"
#include "game.hpp"
#include "point.hpp"
#include "mqttHandler.h"

using namespace std;

class BlindGame : public Game {
private:
    int mapRow;
    int mapCol;
    Point *coinLocation;
    
    int calculateMapRow(int maxPlayer);
    int calculateMapCol(int maxPlayer);
    int findPlayerId();
    bool checkBounds(Point *p);
    bool isValidPoint(Point *p);
    void moveCoin(int dir);
    
    vector<int> getCoinDirections();
    void playCoin(int moveC);
    void placeCoin();
    void placePlayers();
    Point* getRandomCoinPoint();

    
    string distanceTopic;

    
    string positionTopic;

    const string address;

public:
    BlindGame(int id, int maxPlayer, string name);
    vector<pair<int, int>> getCoinDistances();
    int join(string playerName);    
    bool isValidMovement(int dir, Point *p);
    bool movePlayer(int dir, int playerId);
    void resetMoves();
    int isFinished();
    void startGame();
    bool isTurnFinished();
    
    mqttPublisher *distanceSender;
    mqttSubscriber *positionCollecter;
    
    //getters
    int getMaxPlayer();
    int getCurrPlayers();
    Point* getCoinLocation();
    int getId();
    string getName();
    //setters
    void setCurrPlayers(int currPlayers);
    void setTopicNames(string distT,string posT){
        this->distanceTopic = distT;
        this->positionTopic = posT;
    }
    
};


#endif /* blindGame_hpp */
