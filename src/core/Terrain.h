#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <Box2D/Box2D.h>
#include "Perlin.h"

class Terrain {
    public:

	Terrain();
	
	void initTerrain(b2World *w);
	Perlin getPerlin() const;
	b2World *world;
	b2Body *terrainBody;
	Perlin perlin;
	~Terrain();

    private:
	
	
	
	
};

#endif
