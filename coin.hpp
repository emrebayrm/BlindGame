//
//  coin.hpp
//  BlindGame
//
//  Created by Sincap on 17.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#ifndef coin_hpp
#define coin_hpp

#include "blindGamePlayer.hpp"
#include <string>

class BlindGamePlayer;

class Coin : public BlindGamePlayer {
public:
    Coin();
    Coin(int id, string name);
    bool move(int dir);
    string toString();
};

#endif /* coin_hpp */
