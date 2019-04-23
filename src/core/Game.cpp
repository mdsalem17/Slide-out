#include "Game.h"
#include <iostream>

Game::MyContactListener::MyContactListener()
{
    numPoints = 0;
}

void Game::MyContactListener::BeginContact(b2Contact* contact) {
  
        //check if fixture A was a ball
         void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
         if ( bodyUserData )
           static_cast<Player*>( bodyUserData )->startContact();
         
        //check if fixture B was a ball
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if ( bodyUserData )
          static_cast<Player*>( bodyUserData )->startContact();
}
  
void Game::MyContactListener::EndContact(b2Contact* contact) {
  
      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Player*>( bodyUserData )->endContact();
  
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Player*>( bodyUserData )->endContact();
  
}

Game::Game(){

    world = NULL;
    ter = new Terrain;
    player = new Player;

    gravity.Set(0,-9.8/8.0f);
    
    dimx = 900, dimy = 480;

    initBox2dWorld(gravity);
    player->initPlayer(world);
    ter->initTerrain(world);

}

bool Game::isLevelFinished(){
    if(player->getPosition().x > ter->tabHillPoints.back().x ) return true;

    return false;
}
void Game::initBox2dWorld(const b2Vec2 &gravity){

    //bool doSleep = true; //If this is set to true, bodies will sleep when they come to rest, and are excluded from the simulation until something happens to 'wake' them again.
    world = new b2World(gravity);
    world->SetContactListener(&myContactListenerInstance);

}

void Game::updateBox2dWorld(){

    float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
    int32 velocityIterations = 8;   //how strongly to correct velocity
    int32 positionIterations = 3;   //how strongly to correct position

    world->Step(timeStep, velocityIterations, positionIterations); //Step does the update
}

void Game::collision(){
    //double slope = ter->getSlope(player->getPosition().x);
    double slope = ter->getSlope(50/2+getTerrain()->terrainBody->GetLinearVelocity().x);
    //std::cout << "slope value at " << getTerrain()->terrainBody->GetPosition().x << " = " << slope << std::endl; 
    if(!player->isInAir){
        if(slope > 0.5) //positive slope value means the bird is moving up
            player->playerBody->ApplyForce(b2Vec2(-10,-10), player->playerBody->GetWorldCenter(), true);
        else if(slope < 0.5) //negative slope value means the bird is moving down
            player->playerBody->ApplyForce(b2Vec2(50,-50), player->playerBody->GetWorldCenter(), true);
    }
}

Player* Game::getPlayer(){
    return player;
}
Terrain* Game::getTerrain(){
    return ter;
 }
 
Game::~Game(){
    delete world;
    world = NULL;
    delete player;
    player = NULL;
    delete ter;
    ter = NULL;
}