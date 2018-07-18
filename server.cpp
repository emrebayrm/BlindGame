#include <iostream>
#include <cstring>
#include <unistd.h>
#include "engine.hpp"
#include "blindGameServerEngine.hpp"

using namespace std;


int main() {
    BlindGameServerEngine gameServerEngine;
    gameServerEngine.startServer(0);
    return 0;
}