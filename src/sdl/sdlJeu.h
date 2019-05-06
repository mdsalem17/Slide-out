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
     * @brief procédure qui charge un fichier pour vérifier son existence
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
     * @brief procédure qui charge une image depuis un fichier vers un renderer
     * @param filename: Chaîne de caractères contenant le nom du fichier qu'on veut charger
     * @param renderer: Le renderer vers lequel on charge l'image
    */
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    
    /**
     * @brief procédure qui charge une image d'un renderer 
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

    		
	/**		
	* @brief Mutateur qui permet de modifier la surface		
	* \param surf: SDL_Texture *
	*/
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

    Mix_Chunk * StartSound;
    Mix_Chunk * bonusSound;
    Mix_Chunk * LvlUpSound;
    bool withSound;

    //Affichage terrain
    /** 
     * @brief procédure qui permet dessiner le paysage		
	*/
    void drawBackground();

    /**
     * @brief procédure qui permet dessiner le terrain
	*/
    void drawTerrain();

	/**		
	* @brief procédure qui permet dessiner le joueur		
	*/
    void drawPlayer();

    /**		
	* @brief procédure qui permet dessiner le menu, c'est un seul menu qnd on rentre dans le jeu ou quand on perd		
	*/
    void drawMenu();

   /**		
	     * @brief procédure qui permet afficher du texte		
	     * @param text: le texte à afficher		
	     * @param rect: SDL_Rect		
	     * @param color: SDL_Color		
	*/    
    void drawText(string text, SDL_Rect rect, SDL_Color color);

    /**		
	     * @brief fonction qui converti un nobmre en chaine de charactére 
	     * @param nb: le nommbre a convertir
	     * \return string la chaine constitué de l'eniter espacée
	*/    
    string formatNbtoText(int nb);


    /**
     * @brief procédure qui permet de faire un zoom sur le joueur
     * \return float: le coefficient zoom qu'il faut appliquer
     */
    float computeZoomPlayer();


    float angle;

    /**	
     * @brief procédure qui permet de calculer l'angle du joueur
     */
    void calculAngle();
    
    b2Vec2 playerPos;

    //Images Player
    int player_frame;
    int prev_sprite_frame;
    int sprite_frame;
    //Images Player
    Image im_player[7];
    Image im_ladyplayer[7];
    Image im_player_selector;
    //Images Timer
    Image im_timer_bg;
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
    //Image Menu
    Image im_title;
    Image im_gameover;
    Image im_avatar;
    Image im_astuce;
    Image im_espace;

    int seconds;

    int currentLevel;
    float freqLevel[5]; //frequence du bruit de perlin


    /**
     *@brief procédure qui permet de mettre à jour le niveau
    */
    void updateLevel();
     
    bool hasLost;
    bool gameStarted;
    bool PlayerSelectorL;
    bool ResetGame;

    /**		     
	* @brief procédure qui permet de réinitialiser le niveau quand on perd
	*/
    void ResetLevel();

    /**		
	    * @brief procédure qui permet de mettre à jour le status du joueur		
	*/
    void updatePlayerStatus();

    /**		
	* @brief procédure qui permet de selection un joueur		
	* @param RoL(Right or Left): pour décider d'afficher le selecteur à droite ou à gauche		
	*/
    void playerSpriteSelector(char RoL);
    


public:

    sdlJeu ();
    ~sdlJeu ();

    void sdlBoucle ();
    void sdlAff ();

       
    

};




#endif
