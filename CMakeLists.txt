cmake_minimum_required(VERSION 3.10)
project(BlindGame)

set(CMAKE_CXX_STANDARD 11)

link_libraries(paho-mqtt3c)

add_executable(Server server.cpp networkModule.cpp networkModule.hpp game.hpp game.cpp engine.cpp engine.hpp blindGameServerEngine.cpp blindGameServerEngine.hpp blindGame.hpp blindGame.cpp point.hpp point.cpp blindGamePlayer.cpp blindGamePlayer.hpp player.cpp player.hpp dummies/DummyGame.cpp dummies/DummyGame.h dummies/DummyGameServerEngine.cpp dummies/DummyGameServerEngine.h dummies/DummyNetworkModule.h mqttHandler.cpp mqttHandler.h)

add_executable(Client client.cpp networkModule.cpp networkModule.hpp game.hpp game.cpp engine.cpp engine.hpp blindGameServerEngine.cpp blindGameServerEngine.hpp blindGame.hpp blindGame.cpp point.hpp point.cpp blindGamePlayer.cpp blindGamePlayer.hpp player.cpp player.hpp dummies/DummyGame.cpp dummies/DummyGame.h dummies/DummyGameServerEngine.cpp dummies/DummyGameServerEngine.h dummies/DummyNetworkModule.h mqttHandler.cpp mqttHandler.h)

add_executable(mqttPubTest mqttHandler.cpp mqttHandler.h dummies/DummyMqttPubTest.cpp)

add_executable(mqttSubTest mqttHandler.cpp mqttHandler.h dummies/DummyMqttSubTest.cpp)

add_executable(game blindGame.cpp blindGame.hpp game.cpp game.hpp blindGamePlayer.hpp blindGamePlayer.cpp player.hpp player.cpp point.cpp player.hpp mqttHandler.h mqttHandler.cpp)

add_executable(DummyServer TestEngine.cpp networkModule.cpp networkModule.hpp game.hpp game.cpp engine.cpp engine.hpp blindGameServerEngine.cpp blindGameServerEngine.hpp blindGame.hpp blindGame.cpp point.hpp point.cpp blindGamePlayer.cpp blindGamePlayer.hpp player.cpp player.hpp dummies/DummyGame.cpp dummies/DummyGame.h dummies/DummyGameServerEngine.cpp dummies/DummyGameServerEngine.h dummies/DummyNetworkModule.h mqttHandler.cpp mqttHandler.h)
