#include "Game.h"

#include <iostream>
Game::Game(){

    world = NULL;
    gravity.Set(0,-9.8);

    initBox2dWorld(gravity);
    player.initPlayer(world);
    ter.initTerrain();


}
void Game::initBox2dWorld(const b2Vec2 &gravity){

    //bool doSleep = true; //If this is set to true, bodies will sleep when they come to rest, and are excluded from the simulation until something happens to 'wake' them again.
    world = new b2World(gravity/*, doSleep*/);


}

void Game::updateBox2dWorld(){

    float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
    int32 velocityIterations = 8;   //how strongly to correct velocity
    int32 positionIterations = 3;   //how strongly to correct position


    world->Step(timeStep, velocityIterations, positionIterations); //Step does the update

}


Player Game::getPlayer() const{
    return player;
}
Terrain Game::getTerrain() const{
    return ter;

 }



Game::~Game(){
    delete world;
    world = NULL;

}
