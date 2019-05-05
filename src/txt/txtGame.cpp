#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"

#include "../core/Game.h"

void txtAff(WinTXT & win, Game & game) {

	win.clear();
//    for(int i=0; i < 150; i++)
//            for(int j=0; j < 75 ; j++)
//                        win.print(i,j, '-');

    win.print(game.getPlayer()-> getPosition().x,- game.getPlayer()->getPosition().y,'O' );

    for(int i=0; i < 10 ; i++)
        win.print(i, 50, '=');

    for(int i=0 ; i < 40 /*game.getTerrain()->maxHillPoints */; i++){
		
        win.print(game.getTerrain()-> tabHillPoints.at(i).x - 10.0f,
		 game.getTerrain()->tabHillPoints.at(i).y /100.0f , '.');
    }

	win.draw();
}

void txtBoucle (Game &game) {
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
    WinTXT win (1000,1000);
    b2Vec2 t(0,0);
	bool ok = true;
	int c;

	do {
	    txtAff(win,game);

        #ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000); //0.1 sec
        #endif // WIN32


       // std::cout << game.getPlayer().getPosition().x << " : " << game.getPlayer().getPosition().y << std::endl;
        game.updateBox2dWorld();
		c = win.getCh();
		switch (c) {
			case 'k':
				//jeu.actionClavier('g');
                game.getPlayer()->applyForce(b2Vec2(0,-25));
				break;

            case 'p':
                win.pause();
                break;
			case 'q':
				ok = false;
				break;
		}

	} while (ok);

}
