#ifndef PERLIN_H
#define PERLIN_H

#include <Box2D/Box2D.h>
#include <vector>
#include <math.h>

class Perlin
{
    public:
    Perlin();
    Perlin(int _octaves, int _zoomX, int _zoomY, int _offset, double _persistance, double _frequency, int _nbPts);
    
    int getNbPts() const;
    void updatePerlin(int nb);
    b2Vec2 getPtsPerlin(int i);
    std::vector<b2Vec2> tabPerlin;
    void initPerlin();

    ~Perlin();
    private:
    int nbPts;
    int octaves, zoomX, zoomY, offset ;
    double persistance, frequency;

    //configuration Perlin
	double rand_noise(int t);
	double cosine_interp(double a, double b, double t);
	double interp_noise(double x);
	double perlin(int octaves, double frequency, double persistance, double x);
    
};

#endif
