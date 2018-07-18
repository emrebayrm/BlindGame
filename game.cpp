//
// Created by patates on 7/16/18.
//

#include "game.hpp"
#include "player.hpp"

#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

Game::Game(int id, int maxPlayer, string name) {
    printf("%s(%d)\n", __func__, __LINE__);
    this->id = id;
    printf("%s(%d)\n", __func__, __LINE__);
    this->maxPlayer = maxPlayer;
    printf("%s(%d)\n", __func__, __LINE__);
    this->name = name;
    printf("%s(%d)\n", __func__, __LINE__);
    this->currPlayers = 0;
    printf("%s(%d)\n", __func__, __LINE__);
    players.resize(maxPlayer);
    printf("%s(%d)\n", __func__, __LINE__);

}

Player* Game::getPlayer(int playerId) {
    return players[playerId];
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
