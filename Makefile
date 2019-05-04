MKDIRS=obj bin
CORE_DIR = src/core/
INCLUDE_DIR = -IBox2D
INCLUDE_GRAPIC = -I$(GRAPIC_DIR) -I/usr/include/SDL2
INCLUDE_SDL = -I$(SDL_DIR)
LIBS_BOX2D = -LBox2D -lBox2D
LIBS_SDL = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CPPFLAGS = -Wall 

OBJ_DIR = obj/
BIN_DIR = bin/
TXT_DIR = src/txt/
GRAPIC_DIR = src/grapic/
SDL_DIR = src/sdl/
all: $(shell mkdir -p $(MKDIRS)) $(BIN_DIR)gameTxt $(BIN_DIR)mainGrapic

txt: $(BIN_DIR)gameTxt

grapic: $(BIN_DIR)mainGrapic

sdl: $(BIN_DIR)mainSdl

$(BIN_DIR)mainGrapic: $(OBJ_DIR)mainGrapic.o $(OBJ_DIR)Grapic.o $(OBJ_DIR)Game.o $(OBJ_DIR)Player.o  $(OBJ_DIR)Terrain.o 
	g++ $(OBJ_DIR)mainGrapic.o $(OBJ_DIR)Grapic.o $(OBJ_DIR)Game.o $(OBJ_DIR)Player.o  $(OBJ_DIR)Terrain.o $(LIBS_BOX2D) $(LIBS_SDL) -o $(BIN_DIR)mainGrapic

$(BIN_DIR)gameTxt: $(OBJ_DIR)Game.o $(OBJ_DIR)mainTxt.o $(OBJ_DIR)txtGame.o $(OBJ_DIR)winTxt.o $(OBJ_DIR)Player.o $(OBJ_DIR)Terrain.o
	g++ $(OBJ_DIR)Game.o $(OBJ_DIR)mainTxt.o $(OBJ_DIR)txtGame.o $(OBJ_DIR)winTxt.o $(OBJ_DIR)Player.o $(OBJ_DIR)Terrain.o $(LIBS_BOX2D) -o $(BIN_DIR)gameTxt 

$(BIN_DIR)mainSdl: $(OBJ_DIR)mainSdl.o $(OBJ_DIR)sdlJeu.o $(OBJ_DIR)Game.o $(OBJ_DIR)Player.o $(OBJ_DIR)Terrain.o
	g++ $(OBJ_DIR)mainSdl.o $(OBJ_DIR)sdlJeu.o $(OBJ_DIR)Game.o $(OBJ_DIR)Player.o $(OBJ_DIR)Terrain.o $(LIBS_SDL) $(LIBS_BOX2D) -o $(BIN_DIR)mainSdl

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

$(OBJ_DIR)Grapic.o: $(GRAPIC_DIR)Grapic.cpp $(GRAPIC_DIR)Grapic.h
	g++ $(CPPFLAGS) -c $(GRAPIC_DIR)Grapic.cpp $(INCLUDE_GRAPIC) -o $(OBJ_DIR)Grapic.o

$(OBJ_DIR)mainGrapic.o: $(GRAPIC_DIR)mainGrapic.cpp $(GRAPIC_DIR)Grapic.h
	g++ $(CPPFLAGS) -c $(GRAPIC_DIR)mainGrapic.cpp $(INCLUDE_GRAPIC) $(INCLUDE_DIR) -o $(OBJ_DIR)mainGrapic.o

$(OBJ_DIR)sdlJeu.o: $(SDL_DIR)sdlJeu.cpp $(SDL_DIR)sdlJeu.h $(CORE_DIR)Game.h
	g++ $(CPPFLAGS) -c $(SDL_DIR)sdlJeu.cpp $(INCLUDE_SDL) $(INCLUDE_DIR) -o $(OBJ_DIR)sdlJeu.o 

$(OBJ_DIR)mainSdl.o: $(SDL_DIR)mainSdl.cpp $(SDL_DIR)sdlJeu.h
	g++ $(CPPFLAGS) -c $(SDL_DIR)mainSdl.cpp $(INCLUDE_SDL) $(INCLUDE_DIR) -o $(OBJ_DIR)mainSdl.o 
clean:
	rm $(OBJ_DIR)* $(BIN_DIR)*

