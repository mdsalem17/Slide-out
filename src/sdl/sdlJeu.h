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

    /**
     * @brief Charge un fichier pour vérifier son existence
     * @param filename: Chaîne de caractères contenant le chemin du fichier dont on souhaite vérifier son existence
     * \return bool
    */
    bool file_exists (const std::string& name);

public:
    
    /**
     * @brief Constructeur par défaut de la classe image: initialise dimx et dimy à 0
     * ce constructeur n'alloue pas de pixel
    */
    Image () ;
    
    /**
     * @brief Charge une image depuis un fichier vers un renderer
     * @param filename: Chaîne de caractères contenant le nom du fichier qu'on veut charger
     * @param renderer: Le renderer vers lequel on charge l'image
    */
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    
    /**
     * @brief 
     * @param renderer: Le renderer depuis lequel on charge
    */
    void loadFromCurrentSurface (SDL_Renderer * renderer);

    /**
     * @brief  la fonction qui dessine une image (au format rectungulaire)
     * @param renderer: Le renderer sur lequel on dessine
     * @param x: position en x de l'image à dessiner
     * @param y: position en y de l'image à dessiner
     * @param w: largeur de l'image à dessiner
     * @param h: hauteur de l'image à dessiner
     * @param angle: l'angle d'inclinaison de l'image à dessiner
    */
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1, float angle=0);

    
    /**
     * @brief Accesseur qui permet de récuperer le terrain
     * \return SDL_Texture *
    */
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
    void drawBackground();
    void drawTerrain();
    void drawPlayer();
    void drawMenu();
    void drawText(string text, SDL_Rect rect, SDL_Color color);
    float computeZoomPlayer();

    float angle;
    void calculAngle();
    
    b2Vec2 playerPos;

    int player_frame;
    int prev_sprite_frame;
    int sprite_frame;
    //Images Player
    Image im_player[7];
    Image im_player_selector;
    //Images Timer
    Image im_timer_bg;
    Image im_time_up;
    //Images Sky
    Image im_sky[5];
    Image im_sun;
    Image im_cloud;
    //Images Terrain
    Image im_sprite[5];
    Image im_background[5];
    Image im_arrow;
    Image im_arrow2;
    //Images Bonus
    Image im_bonus;
    Image im_score_bg;

    int seconds;
    int start_timer;
    void initTimer(unsigned int editTimer);
    void updateTimer(uint32 t);

    void updateLevel();
    double freqLevel; //frequence du bruit de perlin
    
    bool hasLost;
    bool gameStarted;
    bool PlayerSelectorL;

    void updatePlayerStatus();
    

    void playerSpriteSelector(char RoL);

public:

    sdlJeu ();
    ~sdlJeu ();
    void sdlBoucle ();
    void sdlAff ();
    

};




#endif
