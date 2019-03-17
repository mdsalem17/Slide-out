#include "Terrain.h"

Terrain::Terrain(){
	slop=0;
	nbPts = 200;
	world = NULL;
	
	
}

void Terrain::initTerrain(b2World *w){
	//init tableau de points
	unsigned int numberOfHills=2;
	unsigned int pixelStep=2;
	for(int i = 0 ; i < nbPts ; i++)
	{
		tabHeight.push_back(b2Vec2(i*2.5, cos(i*50)*2.5));
	}


	world = w;

	//body
	b2BodyDef terrainBodyDef;
	terrainBodyDef.type = b2_staticBody; //this will be a dynamic body
  	terrainBodyDef.position.Set(0,0); //set the starting position
  	terrainBodyDef.angle = 0; //set the starting angle

	terrainBody = world->CreateBody(&terrainBodyDef);

	//shape
	b2ChainShape chain;

	chain.CreateChain(tabHeight.data(), nbPts);

	//fixture
	b2FixtureDef terrainFixtureDef;
	terrainFixtureDef.shape = &chain;
	terrainFixtureDef.density = 1;

	terrainBody->CreateFixture(&terrainFixtureDef);
	
}
	
float Terrain::getHeight() const{
	//return tabHeight[1];
	return 0.0;
}
	
float Terrain::getSlop() const{
	return 0.0;
	
}


Terrain::~Terrain(){
	slop=0;
	// delete terrainBodyDef;
	// terrainBodyDef = NULL;
}
	