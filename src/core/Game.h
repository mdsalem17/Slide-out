#ifndef JEU_H
#define JEU_H

#include "Player.h"
#include "Terrain.h"

class Game
{
public:
    Game();

    ~Game();

    int dimx;
    int dimy;
     
    b2Vec2 gravity;
    b2World* world;

    void initBox2dWorld(const b2Vec2 &gravity);
    void updateBox2dWorld();


    Player* getPlayer();
    Terrain* getTerrain();


private:
    Player *player;
    Terrain *ter;




};

#endif
