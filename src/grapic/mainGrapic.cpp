#include <Grapic.h>
#include "../core/Game.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

using namespace grapic;

const int DIMW = 700 ;
const int DIM = 9;
const int DIM_SPRITE = 32;

void init(Game & game)
{
    game.getPlayer().applyForce(b2Vec2(250,35));
}

void draw(const Game & game, float & range)
{
    color(255,0,0);
    circleFill(game.getPlayer().getPosition().x, -game.getPlayer().getPosition().y, 5);

    // => pour le tout le tableau 
    for(int i = range ; i < 30+range ; i++)
    {
        float32 x1,x2,y1,y2 ;
        x1 = 10*(game.getTerrain().tabHeight.at(i).x) - range*50;
        x2 = 10*(game.getTerrain().tabHeight.at(i+1).x) - range*50 ;
        y1 = 150+game.getTerrain().tabHeight.at(i).y;
        y2 = 150+game.getTerrain().tabHeight.at(i+1).y;
        color(255, 255, 255);
        circleFill(x1, y1, 3);
        circleFill(x2, y2, 3);
        line( x1, y1, x2, y2 );
    }

    //isKeyPressed(SDLK_RIGHT) &&
    if (range < game.getTerrain().getnbPts()-30)
    {
        if(isKeyPressed(SDLK_SPACE))
        {
            #ifdef _WIN32
            Sleep(100);
            #else
            usleep(100000); //0.1 sec
            #endif // WIN32
            range = range + 0.05f ;
        }
        #ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000); //0.1 sec
        #endif // WIN32
        range++;
    }
}

void update(Game & game)
{   
    game.updateBox2dWorld();
}


int main(int , char ** )
{
    float part = 0; 
	Game game ;
    bool stop=false;
	winInit("SlideOut", DIMW*2,DIMW);
    setKeyRepeatMode(true); 
    init(game);
	while( !stop )
    {
        backgroundColor( 100, 80, 200, 255 );
        winClear();
        update(game);
        draw(game,part);     
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

