//
// Created by patates on 7/16/18.
//

#ifndef BLINDGAME_GAME_H
#define BLINDGAME_GAME_H

#include <vector>
#include <string>
#include <set>
#include "player.hpp"

using namespace std;

class Game {
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
    void pushPlayer(Player* player){
        players.push_back(player);
        ++currPlayers;
    }
    Game(int id, int maxPlayer, string name);
    int getId();
    vector<Player*> getPlayers();
    int getMaxPlayer();
    int getCurrPlayers();
    string getName();
    Player* getPlater(int playerId);

    virtual string toString();
    
    //adds the player to the game. Returns playerId
    virtual int join(string playerName) = 0;
    
    //returns true if the game is finished, false otherwise
    virtual bool isFinished() = 0;

};

#endif //BLINDGAME_GAME_H
