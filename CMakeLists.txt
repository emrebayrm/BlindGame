cmake_minimum_required(VERSION 3.10)
project(BlindGame)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server server.cpp Engine.cpp Engine.h Game.cpp Game.h Packets.h blindGame.hpp blindGame.cpp point.cpp point.hpp player.hpp player.cpp NetworkModule.cpp NetworkModule.h)
