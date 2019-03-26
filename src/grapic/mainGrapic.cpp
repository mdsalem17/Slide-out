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

void init(Game & game, Perlin & perlin, bool &hasPressed)
{
    game.getPlayer().setPosition(b2Vec2(DIMW/2, DIMW/2),0);
    game.getPlayer().applyForce(b2Vec2(250,35));
    hasPressed = false;
}

void draw(const Game & game, Perlin perlin, float & range)
{
    color(255,255,255);
    int radius = 10 ;
    circleFill(game.getPlayer().getPosition().x, game.getPlayer().getPosition().y+radius, radius);  
    
    for(int i = 1 ; i < perlin.getNbPts() ; i++){
        line((i-1), perlin.getPtsPerlin(i-1).y, i , perlin.getPtsPerlin(i).y);
    }
}

void update(Game & game, Perlin & perlin, bool &hasPressed)
{   
    game.updateBox2dWorld();
   
    //force par defaut
    game.getPlayer().applyForce(b2Vec2(1,1.5));
   
    //reset au debut pour debug
    if(game.getPlayer().getPosition().x > DIMW*2){
       game.getPlayer().setPosition(b2Vec2(0,100),0);

    }
    if(isKeyPressed(SDLK_DOWN)) {
        hasPressed = true;
    }

    if(hasPressed){
        game.getPlayer().dive();
    }


    
    

    //appel updatePerlin();
}

int main(int , char ** )
{
    float part = 0; 	
    Game game ;
    Perlin perlin;
    bool hasPressed;
    bool stop=false;
	winInit("SlideOut", DIMW*2,DIMW);
    setKeyRepeatMode(true); 
    init(game, perlin, hasPressed);
	while( !stop )
    {
        backgroundColor( 100, 80, 200, 255 );
        winClear();
        update(game, perlin, hasPressed);
        draw(game, perlin, part);     
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

