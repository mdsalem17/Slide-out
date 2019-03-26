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
    playerBodyDef.position.Set(0,0); //set the starting position

    //reduce the world velocity of bodies =/= friction (friction occurs w/ contact)
    playerBodyDef.linearDamping = 0.07f;

   
    playerBody = world->CreateBody(&playerBodyDef);

    //Setting & creating the fixture
    //To define shape, size etc.. of our object
    b2FixtureDef playerFixture;

    b2CircleShape circleShape;
    circleShape.m_radius = .85;
    playerFixture.shape = &circleShape;
    //bounciness
    playerFixture.restitution = .25;
    
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

void Player::setPosition(b2Vec2 pos, float32 angle){

    //apply immediate force
    playerBody->SetTransform(pos, angle);
}

void Player::dive(){
    playerBody->ApplyForce(b2Vec2(0,-30), playerBody->GetWorldCenter(), true);
}



Player::~Player(){



}
