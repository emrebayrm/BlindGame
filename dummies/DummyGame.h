//
// Created by patates on 7/17/18.
//

#ifndef BLINDGAME_DUMMYGAME_H
#define BLINDGAME_DUMMYGAME_H

#include "../game.hpp"

class DummyGame : public Game{
private:
    int uid = 0;
public:
    DummyGame(int id, int maxPlayer, const string &name);

    int join(string playerName) override;

    bool isFinished() override;

};

class DummyPlayer : public Player{
public:
    DummyPlayer(int id, const string &name);

    string toString() override;

};

#endif //BLINDGAME_DUMMYGAME_H
