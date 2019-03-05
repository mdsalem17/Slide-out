INCLUDE_DIR = -Isrc/core/Box2D2
LIBS_BOX2D = -Lsrc/core/Box2D2 -lBox2D
CPPFLAGS = -Wall 

all: gameTxt

gameTxt: Game.o mainTxt.o txtGame.o winTxt.o Player.o
	g++ Game.o mainTxt.o txtGame.o winTxt.o Player.o -o gameTxt $(LIBS_BOX2D) 

Game.o: src/core/Game.cpp src/core/Game.h
	g++ $(CPPFLAGS) -c src/core/Game.cpp $(INCLUDE_DIR)

Player.o: src/core/Player.cpp src/core/Player.h
	g++ $(CPPFLAGS) -c src/core/Player.cpp $(INCLUDE_DIR)

Terrain.o: src/core/Terrain.cpp
	g++ $(CPPFLAGS) -c src/core/Terrain.cpp  

mainTxt.o: src/txt/mainTxt.cpp src/txt/txtGame.h src/txt/winTxt.h
	g++ $(CPPFLAGS) -c src/txt/mainTxt.cpp $(INCLUDE_DIR) 

txtGame.o: src/txt/txtGame.cpp src/txt/winTxt.h src/core/Game.h
	g++ $(CPPFLAGS) -c src/txt/txtGame.cpp $(INCLUDE_DIR) 

winTxt.o: src/txt/winTxt.cpp src/txt/winTxt.h
	g++ $(CPPFLAGS) -c src/txt/winTxt.cpp $(INCLUDE_DIR) 




