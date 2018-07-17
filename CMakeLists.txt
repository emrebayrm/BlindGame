cmake_minimum_required(VERSION 3.10)
project(BlindGame)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server server.cpp engine.cpp engine.hpp game.cpp game.hpp packets.hpp blindGame.hpp blindGame.cpp point.cpp point.hpp player.hpp player.cpp networkModule.cpp networkModule.hpp engine.cpp)
