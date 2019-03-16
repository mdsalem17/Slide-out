#ifndef TERRAIN_H
#define TERRAIN_H

#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>


class Terrain {
    public:
	Terrain();
	~Terrain();
	std::vector<b2Vec2> tabHeight;
	void initTerrain();

    private:
	float slop;
	unsigned int pixelScale;
	
	
	float getHeight() const;
	float getSlop() const;


};

#endif
