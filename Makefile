testengine:
	g++ -std=c++11 client.cpp engine.cpp engine.hpp networkModule.cpp networkModule.hpp blindGameServerEngine.cpp blindGameServerEngine.hpp point.cpp point.hpp game.cpp game.hpp blindGame.cpp blindGame.hpp blindGamePlayer.cpp blindGamePlayer.hpp player.cpp player.hpp mqttHandler.cpp mqttHandler.h -c
	g++ -std=c++11 client.o engine.o networkModule.o blindGameServerEngine.o blindGame.o point.o game.o blindGamePlayer.o player.o mqttHandler.o -o client -l paho-mqtt3c
gametest:
	g++ -std=c++11 blindGameStub.cpp blindGame.cpp game.cpp point.cpp blindGamePlayer.cpp player.cpp  -o gameTest

testserver:
	g++ -std=c++11 server.cpp engine.cpp engine.hpp networkModule.cpp networkModule.hpp blindGameServerEngine.cpp blindGameServerEngine.hpp point.cpp point.hpp game.cpp game.hpp blindGame.cpp blindGame.hpp blindGamePlayer.cpp blindGamePlayer.hpp player.cpp player.hpp mqttHandler.h mqttHandler.cpp -c
	g++ -std=c++11 server.o engine.o networkModule.o blindGameServerEngine.o blindGame.o point.o game.o blindGamePlayer.o player.o mqttHandler.o -o server -l paho-mqtt3c

compile: testserver testengine
	

cleanserver:
	rm *.o
	rm *.gch
	rm server

cleangametest:
	rm *.o
	rm gametest
cleantestengine:
	rm *.o
	rm *.gch
	rm client
