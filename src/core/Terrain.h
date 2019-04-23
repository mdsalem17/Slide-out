#ifndef TERRAIN_H
#define TERRAIN_H

#include "Perlin.h"

#include <vector>
#include <iostream>

#include <Box2D/Box2D.h>

#define HILLSTEP 20
class Terrain {
    public:

	Terrain();
	
	void initTerrain(b2World *w);
	Perlin* getPerlin();
	b2World *world;
	b2Body *terrainBody;

	int maxHillPoints;
	void generateHillPoints();
	std::vector<b2Vec2> tabHillPoints;

	int terrainResolution; //How apart terrain points are
	double getSlope(int pos);
	
	~Terrain();

    private:

	////////////////////////////////////
	//////// PERLIN
	///////////////////////////////////
	double rand_noise(int t);
	double cosine_interp(double a, double b, double t);
	double interp_noise(double x);
	double computePerlin(int octaves, double frequency, double persistance, double x);
	
	
	
	
};

#endif
