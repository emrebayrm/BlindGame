#include <iostream>
#include <cstring>
#include <unistd.h>
#include "engine.hpp"

using namespace std;


int main() {
    GameServerEngine gameServerEngine;
    gameServerEngine.startServer();
    return 0;
}