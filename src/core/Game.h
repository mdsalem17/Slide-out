#ifndef JEU_H
#define JEU_H

#include "Player.h"
#include "Terrain.h"

/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */ 


/** \defgroup moduleGame module de getsion du jeu
 *
 * \brief chef d'orshestre qui permet de gerer les interactions entre les differents objets du jeu(terrain/player).
 */
  
class Game
{
    public:
     
        /**
          * @brief dimension de la fenetre en x
          *
        */
        int dimx;
        /**
          * @brief dimension de la fenetre en y
          *
        */
        int dimy;

        /**
          * @brief variable contenant le score
          *
        */
        int score;
        /**
          * @brief variable contenant le nombre de bonus récupéré dans le jeu
          *
        */
        int bonus_score;
        
        /**
          * @brief variable contenant le vecteur de la force de la gravité
          *
        */
        b2Vec2 gravity;
        /**
          * @brief variable contenant le monde de Box2D
          *
        */
        b2World* world;
        /**
          * @brief variable contenant le tableau des bonus
          *
        */
        std::vector<b2Vec2> BonusPoints;

    /**
        @brief Constructeur par défaut de la classe Game: initialise dimx et dimy
                ce constructeur n'alloue pas de World
                il instancie un objet de classe Terrain, et un autre de classe Player
    */
        Game();

        /**
            @brief fonction qui determine si le niveau est terminé
        */
        bool isLevelFinished();

        /**
            \brief fonction qui initialise la donnée membre world
            \param gravity: la force de gravité appliquée sur le monde
        */
        void initBox2dWorld(const b2Vec2 &gravity);

        /**
            \brief procédure qui met à jour le monde
        */
        void updateBox2dWorld();
        /**
            \brief procédure qui permet d'ajouter des bonus tout au long du terrain
        */
        void addBonusPoints();
        /**
            \brief procédure qui de gérer les collisions du joueur et d'agmenter le score en fonctions des pentes
        */
        void collision();
        /**
            \brief fonction qui détruit les collisions du terrain et le tableau contenant les points à la fin du niveau
        */
        void destroyTerrain();
        /**
            @brief fonction qui permet de récupérer la position relative du joueur 
        */
        b2Vec2 &getRelativePlayerPos();
        
        /**
            @brief fonction qui permet de récupérer la position relative du Terrain 
        */
        b2Vec2 &getRelativeTerrainPos(); 

    /**
     *     \brief Accesseur : permet d'acceder à l'objet Player instancié par cette classe
     *     \return Terrain
    */
        Player* getPlayer();


    /**
     * @brief Accesseur : permet d'acceder à l'objet Terrain instancié par cette classe
     * \return Terrain
     */
        Terrain* getTerrain();
    /**
     *  @ingroup moduleGame
     *  @brief classe box2d qui gere les collision entre le joueur et le terrain
     */
        class MyContactListener : public b2ContactListener{
            public:
            int numPoints;
            MyContactListener();
            void BeginContact(b2Contact* contact);
            void EndContact(b2Contact* contact);
        };

    /**
       @brief destructeur de la classe Game
    */
        ~Game();

    private:
        Player *player;
        Terrain *ter;
        MyContactListener myContactListenerInstance;

};

#endif
