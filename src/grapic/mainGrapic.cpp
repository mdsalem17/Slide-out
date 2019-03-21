#include <Grapic.h>
#include "../core/Game.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

#include "../core/Perlin.h"

using namespace grapic;

const int DIMW = 700 ;
const int DIM = 9;
const int DIM_SPRITE = 32;

void init(Game & game, Perlin & perlin)
{
    game.getPlayer().setPosition(b2Vec2(DIMW/2, DIMW/2),0);
    game.getPlayer().applyForce(b2Vec2(250,35));
}

void draw(const Game & game, Perlin perlin, float & range)
{
    color(255,255,0);
    int radius = 5 ;
    circleFill(game.getPlayer().getPosition().x + radius, game.getPlayer().getPosition().y+radius, radius);  
    
    for(int i = 1 ; i < perlin.getNbPts() ; i++){
        line(i-1, perlin.getPtsPerlin(i-1).y, i, perlin.getPtsPerlin(i).y);
    }
}

void keysManager(Game & game, Perlin & perlin){
    if (isKeyPressed(SDLK_UP)){
        std::cout<< "upISpressed";
        game.getPlayer().applyForce( b2Vec2(30,30) );
        perlin.updatePerlin();
    } 
    if (isKeyPressed(SDLK_DOWN)) std::cout<< "oooh way down we go go go go go.(koleo)";
}

void update(Game & game, Perlin & perlin)
{   
    game.updateBox2dWorld();
    keysManager(game,perlin);
    //appel updatePerlin();


}


int main(int , char ** )
{
    float part = 0; 	
    Game game ;
    Perlin perlin;
    bool stop=false;
	winInit("SlideOut", DIMW*2,DIMW);
    setKeyRepeatMode(true); 
    init(game, perlin);
	while( !stop )
    {
        backgroundColor( 100, 80, 200, 255 );
        winClear();
        update(game, perlin);

        draw(game, perlin, part);     
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

