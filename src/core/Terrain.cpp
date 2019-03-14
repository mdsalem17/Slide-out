#include "Terrain.h"

	Terrain::Terrain(){
	tabHeight=NULL;
	
	slop=0;
	
	hills=NULL;
	}
	
	Terrain::~Terrain(){
		delete [] tabHeight;
		delete [] hills;
		slop=0;
	}
	
	void Terrain::initTerrain(){
	unsigned int numberOfHills=2;
	unsigned int pixelStep=2;
	}
	
	float Terrain::getHeight() const{
		//return tabHeight[1];
	}
	
	float Terrain::getSlop() const{
	
	}
