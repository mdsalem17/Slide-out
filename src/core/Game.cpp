#include "Game.h"
#include <iostream>
#include <math.h>

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

    gravity.Set(0,-9.8*1.2/8.0f);
    
    dimx = 900, dimy = 480;
    score = 0;
    bonus_score = 0;

    initBox2dWorld(gravity);
    player->initPlayer(world);
    ter->initTerrain(world);
    addBonusPoints();
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

//Cette fonction détruit les collisions du terrain et le tableau contenant les points
void Game::destroyTerrain(){
    //On efface le tableau contenant les points du Terrain
    ter->tabHillPoints.clear();
    BonusPoints.clear();
    //Destruction des fixtures du Terrain
     for (b2Fixture* f = ter->terrainBody->GetFixtureList(); f; f = f->GetNext()){
         ter->terrainBody->DestroyFixture(f);
    }
}

void Game::addBonusPoints(){
    for(unsigned int i = 1 ; i < ter->tabHillPoints.size()/1000; i++)
    {
        BonusPoints.push_back(b2Vec2(ter->tabHillPoints.at(i*1000)));
        BonusPoints.push_back(b2Vec2(ter->tabHillPoints.at((i*1000)+15)));
        BonusPoints.push_back(b2Vec2(ter->tabHillPoints.at((i*1000)+30)));
        BonusPoints.push_back(b2Vec2(ter->tabHillPoints.at((i*1000)+45)));
        BonusPoints.push_back(b2Vec2(ter->tabHillPoints.at((i*1000)+60)));          
    }
}

void Game::collision(){
    if(!player->isInAir){
        b2Vec2 position = getRelativePlayerPos();
        double slope = ter->getSlope(position.x);
        b2Vec2 vel = player->playerBody->GetLinearVelocity();
        float angle = atan2f(vel.y, vel.x);
    
        if(slope < 0)//negative slope value means the bird is moving down
        {
            player->playerBody->ApplyLinearImpulse(-1*b2Vec2(slope*20, slope*20*sin(angle*180/M_PI)), player->playerBody->GetWorldCenter(), true);
            score += 10;
        }
        if(slope > 0) //positive slope value means the bird is moving up
            score += 1;
    }
}

b2Vec2& Game::getRelativePlayerPos()
{
    //std::cout << "force = " << ter->terrainBody->GetLinearVelocity().x << std::endl;
    //return ter->tabHillPoints.at((unsigned int) (player->playerBody->GetPosition().x+(50/2))/46*5 );
    
    return ter->tabHillPoints.at((unsigned int) ((player->playerBody->GetPosition().x)/3) %8000);
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