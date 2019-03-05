#ifndef JEU_H
#define JEU_H

#include "Player.h"
#include "Terrain.h"

class Game
{
public:
    Game();

    ~Game();


    b2Vec2 gravity;
    b2World* world;

    void initBox2dWorld(const b2Vec2 &gravity);
    void updateBox2dWorld();


    Player getPlayer() const;
    Terrain getTerrain() const;


private:
    Player player;
    Terrain ter;




};

#endif
