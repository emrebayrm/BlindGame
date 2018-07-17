cmake_minimum_required(VERSION 3.10)
project(BlindGame)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server TestEngine.cpp networkModule.cpp networkModule.hpp game.hpp game.cpp engine.cpp engine.hpp blindGameServerEngine.cpp blindGameServerEngine.hpp blindGame.hpp blindGame.cpp point.hpp point.cpp blindGamePlayer.cpp blindGamePlayer.hpp player.cpp player.hpp)
