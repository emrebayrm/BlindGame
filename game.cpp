//
// Created by patates on 7/16/18.
//

#include "game.hpp"
#include "player.hpp"

#include <string>
#include <vector>
#include <set>

using namespace std;

Game::Game(int id, int maxPlayer, string name) {
    this->id = id;
    this->maxPlayer = maxPlayer;
    this->name = name;
    this->currPlayers = 0;
    players.resize(maxPlayer);
}

int Game::findPlayerId() {
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

string Game::toString() {
    return "GameId: " + to_string(getId()) +  "   Game Name: " + getName() + "    " +
           to_string(getCurrPlayers())+"/" +to_string(getMaxPlayer());
}

//getters
int Game::getId() {
    return this->id;
}

vector<Player*> Game::getPlayers() {
    return this->players;
}

int Game::getMaxPlayer() {
    return this->maxPlayer;
}

int Game::getCurrPlayers() {
    return this->currPlayers;
}

string Game::getName() {
    return this->name;
}
