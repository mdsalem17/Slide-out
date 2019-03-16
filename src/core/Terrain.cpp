#include "Terrain.h"

	Terrain::Terrain(){
		slop=0;
	}
	
	Terrain::~Terrain(){
		slop=0;
	}
	
	void Terrain::initTerrain(){
		unsigned int numberOfHills=2;
		unsigned int pixelStep=2;
		for(int i = 0 ; i < 500 ; i++)
		{
			tabHeight.push_back(b2Vec2(i*2.5, cos(i*50)*2.5));
		}
	}
	
	float Terrain::getHeight() const{
		//return tabHeight[1];
        return 0.0;
	}
	
	float Terrain::getSlop() const{
        return 0.0;
	
	}
