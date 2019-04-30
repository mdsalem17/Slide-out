#ifndef SDL_JEU_H_
#define SDL_JEU_H_

#include <string>
#include <iostream>
#include <cassert>

#include "../core/Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

using namespace std; 

//! \brief Pour gerer une image avec SDL2
class Image {

private:

    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;

public:
    
    /**
        @brief Constructeur par défaut de la classe image: initialise dimx et dimy à 0
                ce constructeur n'alloue pas de pixel
    */
    Image () ;
    
    /**
        @brief Charge une image depuis un fichier vers un renderer
        @param filename: Chaîne de caractères contenant le nom du fichier qu'on veut charger
        @param renderer: Le renderer vers lequel on charge l'image
    */
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    
    /**
        @brief 
        @param renderer: Le renderer depuis lequel on charge
    */
    void loadFromCurrentSurface (SDL_Renderer * renderer);

    /**
        @brief 
        @param renderer: Le renderer depuis lequel on charge
        @param x: Le renderer depuis lequel on charge
        @param y: Le renderer depuis lequel on charge
    */
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1, float angle=0);

    
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};



/**
    La classe grant le jeu avec un affichage SDL
*/

class sdlJeu {

private:
	Game jeu;

    SDL_Window * window;
    SDL_Renderer * renderer;

    TTF_Font * font;
    Image font_im;
    SDL_Color font_color;
    Image font_score;
    SDL_Color score_color;

    Mix_Chunk * sound;
    bool withSound;

    //Affichage terrain
    void drawTerrain();
    void drawPlayer();
    void drawTime();
    void getAngle();
    float angle;

    b2Vec2 playerPos;

    int frame;
    //Images Player
    Image im_player0;
    Image im_player1;
    Image im_player2;
    Image im_player3;
    Image im_player4;
    Image selected_player;
    //Images Timer
    Image im_timer_bg;
    Image im_time_up;
    //Images Sky
    Image im_sky;
    Image im_sun;
    Image im_cloud;
    //Images Terrain
    Image im_sprite1;
    Image im_sprite2;
    Image im_sprite3;
    Image im_sprite4;
    Image selected_sprite;

    int seconds; 

public:

    sdlJeu ();
    ~sdlJeu ();
    void sdlBoucle ();
    void sdlAff ();

};




#endif