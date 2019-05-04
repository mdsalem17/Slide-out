#ifndef JEU_H
#define JEU_H

#include "Player.h"
#include "Terrain.h"


/** \defgroup moduleGame module de getsion du jeu
 *
 * \brief chef d'orshestre qui  permet de gerer les interactions entre les differents objets du jeu(terrain/player).
 */
  
class Game
{
    public:
 
    /**
        @brief Constructeur par défaut de la classe Game: initialise dimx et dimy
                ce constructeur n'alloue pas de World
                il instancie un objet de classe Terrain, et un autre de classe Player
    */
        Game();

    /**
       @brief destructeur 
    */
        ~Game();

        int dimx;
        int dimy;
        
        b2Vec2 gravity;
        b2World* world;

        bool isLevelFinished();
        void initBox2dWorld(const b2Vec2 &gravity);
        void updateBox2dWorld();
        
        void collision();
        void destroyTerrain();
        b2Vec2 &getRelativePlayerPos(); 

    /**
     *     @brief Accesseur : permet d'acceder à l'objet player instancié par cette classe
     * \return Terrain
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

    private:
        Player *player;
        Terrain *ter;
        MyContactListener myContactListenerInstance;

};

#endif
