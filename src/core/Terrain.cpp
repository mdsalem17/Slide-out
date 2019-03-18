#include "Terrain.h"

Terrain::Terrain(){
	slop=0;
	nbPts = 500;
	world = NULL;
}

void Terrain::initTerrain(b2World *w){
	//init tableau de points
	for(int i = 0 ; i < nbPts ; i++)
		{	
			float random = rand() % 100 ;
			tabHeight.push_back(b2Vec2(i*5, random*cos(i)*cos(60.0 * M_PI / 180.0)));
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

unsigned int Terrain::getnbPts() const{
	return nbPts;
}

Terrain::~Terrain(){
	slop = 0;
	nbPts = 0 ;
	// delete terrainBodyDef;
	// terrainBodyDef = NULL;
}
	
