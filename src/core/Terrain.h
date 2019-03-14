#ifndef TERRAIN_H
#define TERRAIN_H

#include <Box2D/Box2D.h>


class Terrain {
    public:
	Terrain();
	~Terrain();
	
    private:
	float *tabHeight;
	float slop;
	float *hills;
	unsigned int pixelScale;
	
	
	void initTerrain();
	float getHeight() const;
	float getSlop() const;


};

#endif
