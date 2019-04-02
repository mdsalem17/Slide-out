#ifndef TERRAIN_H
#define TERRAIN_H

#include "Perlin.h"

#include <vector>

#include <Box2D/Box2D.h>

class Terrain {
    public:

	Terrain();
	
	void initTerrain(b2World *w);
	Perlin* getPerlin();
	b2World *world;
	b2Body *terrainBody;
	Perlin *myPerlin;
	
	~Terrain();

    private:
	
	
	
	
};

#endif
