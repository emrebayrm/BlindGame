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
typedef enum {LEFT,RIGHT,UP,DOWN} direction_t;


typedef enum {CREATE, JOIN, OBSERVE,DATA} command_type;

struct Command{
    command_type commandType;
    int length;
    void *context;
};

typedef struct {
    Command command;
    int maxPlayer;
    int gameId;
    char name[MAX_GAME_NAME];
} GameCommand_t;
#endif //BLINDGAME_PACKETS_H
