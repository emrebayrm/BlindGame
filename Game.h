//
// Created by patates on 7/16/18.
//

#ifndef BLINDGAME_GAME_H
#define BLINDGAME_GAME_H

#include <vector>
#include <string>

using namespace std;

class Game{
private:

    char *Name;
    int id;
    vector<char*> player;
    int uid_p = 0;

public:
    Game(int id,int a,char *n){
        this->id = id;
        this->Name = n;
    }

    char *getName(){
        return Name;
    }
    int getId(){
        return id;
    }
    int getMaxPlayer(){
        return 5;
    }
    vector<char*> getPlayers(){
        return player;
    }
    int getMapRow(){
        return 15;
    }
    int getMapCol(){
        return 15;
    }

    int join(char * arr){
        if(player.size() < getMaxPlayer()) {

            player.push_back(arr);
            return uid_p++;
        }
        return -1;
    }
    string toString(){
        string str;
        str.append("Name : ");
        str.append(getName());
        str.append(" Id : " );
        str.append(to_string(getId()));
        str.append("    ");
        str.append(to_string(getMaxPlayer()));
        str.append("/");
        str.append(to_string(getPlayers().size()));
        return str;
    }
};

class BlindGame : public Game{
public:
    BlindGame(int id, int a, char *n);
};


#endif //BLINDGAME_GAME_H
