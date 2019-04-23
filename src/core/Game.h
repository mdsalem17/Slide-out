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
        
        void collision();

        Player* getPlayer();
        Terrain* getTerrain();

        class MyContactListener : public b2ContactListener{
            public:
            int numPoints;
            MyContactListener();
            void BeginContact(b2Contact* contact);
            void EndContact(b2Contact* contact);
        };

    private:
        Player *player;
        Terrain *ter;
        MyContactListener myContactListenerInstance;

};

#endif
