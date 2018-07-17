#include <iostream>
#include <cstring>
#include <unistd.h>
#include "engine.hpp"

using namespace std;


int main() {
    BlindGameServerEngine gameServerEngine;
    gameServerEngine.startServer();
    return 0;
}