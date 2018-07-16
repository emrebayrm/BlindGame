#include <iostream>
#include <cstring>
#include <unistd.h>
#include "Engine.h"

using namespace std;


int main() {
    GameServerEngine gameServerEngine;
    gameServerEngine.startServer();
    return 0;
}