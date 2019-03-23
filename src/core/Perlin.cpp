#include "Perlin.h"

Perlin::Perlin() : 
	octaves(3),
	zoomX(1),
	zoomY(100),
	offset(100),
	persistance(2),
	frequency(.001),
	nbPts(2000)
{
    initPerlin();
}

Perlin::Perlin(int _octaves,int _zoomX,int _zoomY,int _offset,double _persistance, double _frequency, int _nbPts)
{
    octaves = _octaves;
    zoomX = _zoomX;
    zoomY = _zoomY;
    offset = _offset;
    persistance = _persistance;
    frequency = _frequency;

    nbPts = _nbPts;
    initPerlin();
}

double Perlin::rand_noise(int t)
{
	t = (t<<13) ^ t;
	t = (t * (t * t * 15731 + 789221) + 1376312589);
	return 1.0 - (t & 0x7fffffff) / 1073741824.0;
}

double Perlin::cosine_interp(double a, double b, double t)
{
	double c =  (1-cos(t*M_PI)) * .5;
	return (1. - c) * a + c * b;
}

double Perlin::interp_noise(double x)
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

double Perlin::perlin(int octaves, double frequency, double persistance, double x)
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

void Perlin::initPerlin()
{
    for(int i = 0 ; i < nbPts ; i++)
	{
		tabPerlin.push_back(b2Vec2(i, perlin(octaves, frequency, persistance, i) * zoomY + offset));
	}
}
b2Vec2 Perlin::getPtsPerlin(int i)
{
    return tabPerlin.at(i);
}

int Perlin::getNbPts() const
{
	return nbPts ;
}


void Perlin::updatePerlin(int nb)
{
	//defiler le terrain. Aka scrolling
}

Perlin::~Perlin()
{
    nbPts = 0;

    octaves = 0;
    zoomX = 0;
    zoomY = 0;
    offset = 0;
    persistance = 0.0;
    frequency = 0.0;
}
	