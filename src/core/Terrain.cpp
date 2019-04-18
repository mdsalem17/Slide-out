#include "Terrain.h"

	Terrain::Terrain()
	{
		world = NULL;
		maxHillPoints = 5000;
		terrainResolution = 3; //best terrainResolution = 1;
		generateHillPoints();
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
		chain.CreateChain(tabHillPoints.data(), tabHillPoints.size());

		//fixture
		b2FixtureDef terrainFixtureDef;
		terrainFixtureDef.shape = &chain;
		terrainFixtureDef.density = 0;

		terrainBody->CreateFixture(&terrainFixtureDef);
	}

	void Terrain::generateHillPoints(){
		std::cout << "DEBUG START:  Generation de points." << std::endl;
		float yOffset = 200.0f;
		int currentStep = 0;
		std::cout << currentStep << std::endl;
		for(int i = 0 ; i < maxHillPoints;i++){
			tabHillPoints.push_back(b2Vec2(i*terrainResolution,(computePerlin(3,.0011,2,i*terrainResolution) * 200.0f) + yOffset));//(computePerlin(3,.001,2,i) * 200.0f) + yOffset ));
			currentStep += HILLSTEP;
		//	std::cout << currentStep << std::endl;
		}
		std::cout << "DEBUG NB POINTS TOTAL : " << tabHillPoints.size() << std::endl;
		std::cout << "DEBUG END: Generation de points." << std::endl;
		
	}

	int Terrain::getSlope(int pos){
		if(pos > maxHillPoints+2 || pos < 2) return 0;
		else return  (tabHillPoints.at(pos+2).y - tabHillPoints.at(pos-2).y) / (tabHillPoints.at(pos+2).x - tabHillPoints.at(pos-2).x);
	}

////////////////////////////////////
//////// PERLIN
///////////////////////////////////

double Terrain::rand_noise(int t)
{
	t = (t<<13) ^ t;
	t = (t * (t * t * 15731 + 789221) + 1376312589);
	return 1.0 - (t & 0x7fffffff) / 1073741824.0;
}

double Terrain::cosine_interp(double a, double b, double t)
{
	double c =  (1-cos(t*M_PI)) * .5;
	return (1. - c) * a + c * b;
}

double Terrain::interp_noise(double x)
{
	//interpolation entre le point de coord. (x) et celui de coord (x+1)

	//partie entiere
	int integer_part = (int)x;

	//partie fractionnaire
	double fractional_part = x - integer_part;

	//Bruit du point precedent
	double prec = rand_noise(integer_part);
	//Bruit du point suivant
	double suiv = rand_noise(integer_part + 1);

	//Interpolation cosinusoidale
	return cosine_interp(prec, suiv, fractional_part);
}

double Terrain::computePerlin(int octaves, double frequency, double persistance, double x)
{
	//Octaves = nb d'appels a la fonction interp_noise (lissage du bruit)
	//Frequence = frequence de la premiere fonction de bruit lisse
	//Persistence = facteur modifiant l'amplitude de chaque fonction de bruit lisse

	/*  On effectue la somme de n appels a la fonction de bruit lisse (interp_noise), en multipliant a chaque fois la frequence par deux, et l'amplitude par la persistance 
		Pour eviter de sommer chacune d'entre elles, on utilise la formule de la somme des termes d'une suite geometrique (p != 1)
	*/
	double r = 0.;
	double f = frequency;
	double amplitude = 1.;

	for(int i=0 ; i < octaves; i++){
		r+= interp_noise(x*f) * amplitude;
		amplitude *= persistance;
		f*=2;
	}

	double geo_lim = (1 - persistance) / (1 - amplitude);

	return r * geo_lim;
}


	Terrain::~Terrain(){

	}
