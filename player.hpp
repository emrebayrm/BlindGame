//
//  player.hpp
//  BlindGame
//
//  Created by Sincap on 16.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <string>

using namespace std;

class Player {
protected:
    int id;
    string name;
public:
    Player();
    Player(int id, string name);
    int getId();
    string getName();
    
    virtual string toString() = 0;
};

#endif /* player_hpp */
