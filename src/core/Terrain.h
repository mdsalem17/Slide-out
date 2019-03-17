#ifndef TERRAIN_H
#define TERRAIN_H

#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>


class Terrain {
    public:
	Terrain();
	
	std::vector<b2Vec2> tabHeight;
	unsigned int nbPts;
	void initTerrain(b2World *w);

	~Terrain();
    private:
	b2World *world;
    b2Body  *terrainBody;

	float slop;
	unsigned int pixelScale;
	
	float getHeight() const;
	float getSlop() const;


};

#endif
