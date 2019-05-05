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

void init(Game & game, bool &hasPressed)
{
    game.getPlayer()->setPosition(b2Vec2(DIMW/2, DIMW/2),0);
    game.getPlayer()->applyForce(b2Vec2(250,35));
    hasPressed = false;
}

void draw(Game & game, float & range)
{
    color(255,255,255);
    int radius = 10 ;
    circleFill(game.getPlayer()->getPosition().x, 
                DIMW- game.getPlayer()->getPosition().y+radius, radius);  
    //force appliquée par defaut à la balle
    
    for(unsigned int i = 1 ; i < game.getTerrain()->tabHillPoints.size() ; i++){
        line( (i-1), game.getTerrain()->tabHillPoints.at(i-1).y ,i,game.getTerrain()->tabHillPoints.at(i).y);
    }
}

void update(Game & game, bool &hasPressed)
{   
    game.updateBox2dWorld();
   
    //force appliquée par defaut à la balle
    game.getPlayer()->applyForce(b2Vec2(1,1.12));
    game.getPlayer()->playerBody->ApplyForce(b2Vec2(1,.5),game.getPlayer()->playerBody->GetWorldCenter(), true );
    //reset la balle au debut pour debug
    if(game.getPlayer()->getPosition().x > DIMW*2){
        game.getPlayer()->setPosition(b2Vec2(0,100),0);

    }
    if(isKeyPressed(SDLK_DOWN)) {
        hasPressed = true;
    }

    if(hasPressed){
        
        game.getPlayer()->dive();
        hasPressed = false;
    }


    
    

    //appel updatePerlin();
}

int main(int , char ** )
{
    float part = 0; 	
    Game game ;
    bool hasPressed;
    bool stop=false;
	winInit("SlideOut", DIMW*2,DIMW);
    setKeyRepeatMode(true); 
    init(game, hasPressed);
	while( !stop )
    {
        backgroundColor( 100, 80, 200, 255 );
        winClear();
        update(game, hasPressed);
        draw(game, part);     
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

