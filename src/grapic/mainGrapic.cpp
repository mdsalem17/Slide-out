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
    color(255,255,255);
    int radius = 10 ;
    circleFill(game.getPlayer().getPosition().x, game.getPlayer().getPosition().y+radius, radius);  
    
    for(int i = 1 ; i < perlin.getNbPts() ; i++){
        line(i-1, perlin.getPtsPerlin(i-1).y, i, perlin.getPtsPerlin(i).y);
    }
}

void update(Game & game, Perlin & perlin)
{   
    game.updateBox2dWorld();
    bool isInAir = false;
    //TODO : tester la collision, set isInAir en fonction de la valeur
    //Appliquer une force au joueur, tester s'il est en l'air ou pas 
    if(isKeyPressed(SDLK_RIGHT)) {
            game.getPlayer().applyForce(b2Vec2(250,-10));
            game.world->SetGravity(b2Vec2(0,-500));

    }
            
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

