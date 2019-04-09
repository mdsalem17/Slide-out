#ifndef PLAYER_H
#define PLAYER_H

#include <Box2D/Box2D.h>

class Player {
    public:

        Player();

        void initPlayer(b2World *w);


        const b2Vec2& getPosition() const;
        const b2Vec2& getVelocity() const;

        void applyForce(b2Vec2 force);
        void setPosition(b2Vec2 pos, float32 angle);
        b2Body  *playerBody;

        bool isDiving;
        void dive();
        void wake();
        void updateMovement();
        ~Player();

    private:
            b2World *world;
            



};

#endif
