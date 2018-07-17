//
// Created by patates on 7/16/18.
//

#ifndef BLINDGAME_GAME_H
#define BLINDGAME_GAME_H

#include "player.hpp"

#include <vector>
#include <string>
#include <set>

using namespace std;

class Game{
protected:
    set<int> playerIdSet;
    int id;
    vector<Player*> players;
    int maxPlayer;
    int currPlayers;
    string name;
    
    //finds a valid id for a player. Returns -1 if cannot find
    int findPlayerId();
public:
    Game(int id, int maxPlayer, string name);
    int getId();
    vector<Player*> getPlayers();
    int getMaxPlayer();
    int getCurrPlayers();
    string getName();
    
    
    virtual string toString() = 0;
    
    //adds the player to the game. Returns playerId
    virtual int join(string playerName) = 0;
    
    //returns true if the game is finished, false otherwise
    virtual bool isFinished() = 0;

};

#endif //BLINDGAME_GAME_H
