#include "Player.h"

Player::Player(){

  world = NULL;
  playerBody = NULL;

}

//Inits the player and adds it to the box2D world
void Player::initPlayer(b2World *w){
    world = w;

    //Setting & creating the body
    //To define mass, position, physics type  of our object
    b2BodyDef playerBodyDef;

    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(10,-49); //set the starting position
    playerBodyDef.angle = 0; //set the starting angle

    playerBody = world->CreateBody(&playerBodyDef);

    //Setting & creating the fixture
    //To define shape, size etc.. of our object
    b2FixtureDef playerFixture;

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);
    playerFixture.shape = &boxShape;
    playerFixture.density = 1;

    playerBody->CreateFixture(&playerFixture);

}


const b2Vec2& Player::getPosition() const{
    return playerBody->GetPosition();

}


const b2Vec2& Player::getVelocity() const{
    return playerBody->GetLinearVelocity();

}

void Player::applyForce(b2Vec2 force){

    //apply immediate force
    playerBody->ApplyLinearImpulse(force, playerBody->GetWorldCenter(), true);
}





Player::~Player(){



}
