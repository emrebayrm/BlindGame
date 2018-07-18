//
// Created by patates on 7/17/18.
//

#include "DummyGame.h"

int DummyGame::join(string playerName) {
    if(currPlayers == maxPlayer)
        return -1;
    int playerId;
    playerId = findPlayerId();
    Player *player = new DummyPlayer(playerId, playerName);
    getPlayers()[playerId] = player;
    currPlayers++;
    return playerId;
}

bool DummyGame::isFinished() {
    return false;
}

DummyGame::DummyGame(int id, int maxPlayer, const string &name) : Game(id, maxPlayer, name) {

}

DummyPlayer::DummyPlayer(int id, const string name) : Player(id, name) {}

string DummyPlayer::toString() {
    return to_string(getId()) + "  " + getName();
}
