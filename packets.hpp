//
// Created by patates on 7/16/18.
//

#ifndef BLINDGAME_PACKETS_H
#define BLINDGAME_PACKETS_H

#include "networkModule.hpp"

#define MAX_TOPIC_NAME 20
#define MAX_LISTEN 20
#define MAX_GAME 20
#define MAX_PLAYER 10
#define MAX_PLAYER_NAME 30
#define MAX_GAME_NAME 20


struct Game_topics_info{
    char position_tpc[MAX_TOPIC_NAME]; // pos_id
    char distance_tpc[MAX_TOPIC_NAME]; // dist_id
};


typedef enum {CREATE, JOIN, OBSERVE,DATA} command_type;

struct Command{
    command_type commandType;
    int length;
    char context[0];
};

//TODO: all operations commad_t
typedef struct {
    int maxPlayer;
    char gameName[MAX_GAME_NAME];
} GameCreateCommand_t;

typedef struct {
    int gameId;
    char playerName[MAX_PLAYER_NAME];
} GameJoinCommand_t;

typedef struct {
    int gameId;
} GameObserveCommand_t;

typedef struct {
    char data[MAX_PAYLOAD];
} GameDataCommand_t;
#endif //BLINDGAME_PACKETS_H
