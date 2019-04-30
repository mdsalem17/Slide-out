#ifndef TERRAIN_H
#define TERRAIN_H

#include "Perlin.h"

#include <vector>
#include <iostream>

#include <Box2D/Box2D.h>

#define HILLSTEP 20


/** \defgroup moduleTerrain module de getsion du Terrain
 *
 * \brief Le terrain est le modulde qui genere les collines(hills) en utilisant le bruit de perlin
 */

class Terrain {
    public:

    /**
	 * @brief Constructeur par défaut de la classe Terrain: initialise le parametrage du terrain, tel que
     *le nombre de points (maxHillPoints) consituant la forme spatiale du paysage
	 * et la resolution du terrain.Ensuite genere le terrain avec les valuers spécifié.
	 * 
    */
	Terrain();
	
	   /**
	 * @brief Constructeur par défaut de la classe Terrain: initialise le parametrage du terrain, tel que
     *le nombre de points (maxHillPoints) consituant la forme spatiale du paysage
	 * et la resolution du terrain.Ensuite genere le terrain avec les valuers spécifié.
	 * 
    */
	void initTerrain(b2World *w);
	Perlin* getPerlin();
	b2World *world;
	b2Body *terrainBody;

	int maxHillPoints;
	void generateHillPoints();
	std::vector<b2Vec2> tabHillPoints;

	int terrainResolution; //How apart terrain points are
	double getSlope(int pos);
	


    /**
       @brief destructeur de la class Terrain
    */
	~Terrain();

    private:

	////////////////////////////////////
	//////// PERLIN
	///////////////////////////////////
	double rand_noise(int t);
	double cosine_interp(double a, double b, double t);
	
	
	/**
	 * @brief Interpolation cosinusoidale
	 * 
	 * @param x nombre de...
    */
	double interp_noise(double x);


	/**
	 * @brief On effectue la somme octave appels a la fonction de bruit lisse (interp_noise), en multipliant a chaque fois la frequence par deux, et l'amplitude par la persistance 
	 * Pour eviter de sommer chacune d'entre elles, on utilise la formule de la somme des termes d'une suite geometrique (p != 1)  
	 * 
	 * @param octaves nombre d'appels à la fonction interp_noise (lissage du bruit)
	 * @param frequence frequence de la premiere fonction de bruit lisse
	 * @param persistence facteur modifiant l'amplitude de chaque fonction de bruit lisse	 
    */
	double computePerlin(int octaves, double frequency, double persistance, double x);
	
	
	
	
};

#endif
