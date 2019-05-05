#include "txtGame.h"
#include "winTxt.h"
#include <iostream>

#include <Box2D/Box2D.h>

int main(){
    Game game;

    termClear();

    //std::cout << game.getPlayer().getPosition().x << " : " << game.getPlayer().getPosition().y << std::endl;
    game.getPlayer()->applyForce(b2Vec2(250,35));
    txtBoucle(game);

    termClear();




    return 0;
}
