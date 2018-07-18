cmake_minimum_required(VERSION 3.10)
project(BlindGame)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server server.cpp networkModule.cpp networkModule.hpp game.hpp game.cpp engine.cpp engine.hpp blindGameServerEngine.cpp blindGameServerEngine.hpp blindGame.hpp blindGame.cpp point.hpp point.cpp blindGamePlayer.cpp blindGamePlayer.hpp player.cpp player.hpp dummies/DummyGame.cpp dummies/DummyGame.h dummies/DummyGameServerEngine.cpp dummies/DummyGameServerEngine.h dummies/DummyNetworkModule.h mqttHandler.cpp mqttHandler.h)

add_executable(Client client.cpp networkModule.cpp networkModule.hpp game.hpp game.cpp engine.cpp engine.hpp blindGameServerEngine.cpp blindGameServerEngine.hpp blindGame.hpp blindGame.cpp point.hpp point.cpp blindGamePlayer.cpp blindGamePlayer.hpp player.cpp player.hpp dummies/DummyGame.cpp dummies/DummyGame.h dummies/DummyGameServerEngine.cpp dummies/DummyGameServerEngine.h dummies/DummyNetworkModule.h mqttHandler.cpp mqttHandler.h dummies/DummyMqttTest.cpp)

link_libraries(paho-mqtt3c)
add_executable(mqttTest mqttHandler.cpp mqttHandler.h dummies/DummyMqttTest.cpp)

