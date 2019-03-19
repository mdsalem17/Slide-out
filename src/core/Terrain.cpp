#include "Terrain.h"

	Terrain::Terrain()
	{
		world = NULL;
	}
	
	float Terrain::getSlop() const{
        return 0.0;
	
	}

	void Terrain::initTerrain(b2World *w){
		world = w;

		//body
		b2BodyDef terrainBodyDef;
		terrainBodyDef.type = b2_staticBody; //this will be a dynamic body
		terrainBodyDef.position.Set(0,0); //set the starting position
		terrainBodyDef.angle = 0; //set the starting angle

		terrainBody = world->CreateBody(&terrainBodyDef);

		//shape
		b2ChainShape chain;

		chain.CreateChain(perlin.tabPerlin.data(), perlin.getNbPts());

		//fixture
		b2FixtureDef terrainFixtureDef;
		terrainFixtureDef.shape = &chain;
		terrainFixtureDef.density = 1;

		terrainBody->CreateFixture(&terrainFixtureDef);
	}

	
	Terrain::~Terrain(){

	}
