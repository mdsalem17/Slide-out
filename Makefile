MKDIRS=obj bin
CORE_DIR = src/core/
INCLUDE_DIR = -I Box2D
LIBS_BOX2D = -L Box2D -lBox2D
CPPFLAGS = -Wall 

OBJ_DIR = obj/
BIN_DIR = bin/
TXT_DIR = src/txt/

all: $(shell mkdir -p $(MKDIRS)) $(BIN_DIR)gameTxt

$(BIN_DIR)gameTxt: $(OBJ_DIR)Game.o $(OBJ_DIR)mainTxt.o $(OBJ_DIR)txtGame.o $(OBJ_DIR)winTxt.o $(OBJ_DIR)Player.o $(OBJ_DIR)Terrain.o
	g++ $(OBJ_DIR)Game.o $(OBJ_DIR)mainTxt.o $(OBJ_DIR)txtGame.o $(OBJ_DIR)winTxt.o $(OBJ_DIR)Player.o $(OBJ_DIR)Terrain.o $(LIBS_BOX2D) -o $(BIN_DIR)gameTxt 

$(OBJ_DIR)Game.o: $(CORE_DIR)Game.cpp $(CORE_DIR)Game.h
	g++ $(CPPFLAGS) -c $(CORE_DIR)Game.cpp $(INCLUDE_DIR) -o $(OBJ_DIR)Game.o

$(OBJ_DIR)Player.o: $(CORE_DIR)Player.cpp $(CORE_DIR)Player.h
	g++ $(CPPFLAGS) -c $(CORE_DIR)Player.cpp $(INCLUDE_DIR) -o $(OBJ_DIR)Player.o

$(OBJ_DIR)Terrain.o: $(CORE_DIR)Terrain.cpp $(CORE_DIR)Terrain.h
	g++ $(CPPFLAGS) -c $(CORE_DIR)Terrain.cpp  $(INCLUDE_DIR) -o $(OBJ_DIR)Terrain.o

$(OBJ_DIR)mainTxt.o: $(TXT_DIR)mainTxt.cpp $(TXT_DIR)txtGame.h $(TXT_DIR)winTxt.h
	g++ $(CPPFLAGS) -c $(TXT_DIR)mainTxt.cpp $(INCLUDE_DIR) -o $(OBJ_DIR)mainTxt.o

$(OBJ_DIR)txtGame.o: $(TXT_DIR)txtGame.cpp $(TXT_DIR)winTxt.h $(CORE_DIR)Game.h
	g++ $(CPPFLAGS) -c $(TXT_DIR)txtGame.cpp $(INCLUDE_DIR) -o $(OBJ_DIR)txtGame.o  

$(OBJ_DIR)winTxt.o: $(TXT_DIR)winTxt.cpp $(TXT_DIR)winTxt.h
	g++ $(CPPFLAGS) -c $(TXT_DIR)winTxt.cpp $(INCLUDE_DIR) -o $(OBJ_DIR)winTxt.o   

clean:
	rm $(OBJ_DIR)* $(BIN_DIR)* 


