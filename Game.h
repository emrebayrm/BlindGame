//
// Created by patates on 7/16/18.
//

#ifndef BLINDGAME_GAME_H
#define BLINDGAME_GAME_H

#include <vector>
#include <string>
#include "player.hpp"

using namespace std;

class Game{
private:
    int uid_p = 0;
    vector<Player*> players;
public:
    virtual string getName() = 0;
    virtual int getId() = 0;
    virtual int getMaxPlayer() = 0;
    vector<Player*> getPlayers() {
        return players;
    };

    virtual int getMapRow() = 0;
    virtual int getMapCol() = 0;

    virtual string toString() = 0;

    virtual int join(string arr) = 0;

};
/*
class BlindGame : public Game{
public:
    BlindGame(int id, int a, char *n);
};
*/

#endif //BLINDGAME_GAME_H
