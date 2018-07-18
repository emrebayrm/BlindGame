//
//  blindGameStub.cpp
//  BlindGame
//
//  Created by Sincap on 18.07.2018.
//  Copyright © 2018 Sincap. All rights reserved.
//

#include <iostream>
#include "blindGame.hpp"
#include "blindGamePlayer.hpp"

using namespace std;

int main(void) {
    BlindGame *game = new BlindGame(0, 3, "myGame");
    
    game->join("emre");
    game->join("oguz");
    game->join("sincap");
    
    game->startGame();
    int playerId,dir;
    
    
    int win;
    while((win = game->isFinished()) == -1) {
        cout << "coinLocation: x: " << game->getCoinLocation()->getX() << " y: " << game->getCoinLocation()->getY() << endl;
        vector<pair<int,int>> dists = game->getCoinDistances();
        cout << endl << "***distances***" << endl;
        for(int i = 0; i < dists.size(); ++i) {
            cout << "playerId: " << dists[i].first << " dist: " << dists[i].second << endl;
        }
        cout << "*******" << endl;
        for(int i = 0; i < game->getCurrPlayers(); ++i) {
            BlindGamePlayer *player = ((BlindGamePlayer*) game->getPlayers()[i]);
            cout << player->getId() << "- " << player->getName() << " " << player->getLocation()->getX() << " " << player->getLocation()->getY() << "  " << player->getCurrMove() << "/"  << player->maxMove << endl;
        }
        cout << "enter playerId to play" << endl;
        cin >> playerId;
        cout << "enter direction (0-UP , 1-Rigth, 2-down, 3-left)" << endl;
        cin >> dir;
        
        game->movePlayer(dir, playerId);
        
    }
    cout << win << " playerId Wins!!!!!!!" << endl;
    return 0;
}
