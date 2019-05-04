#ifndef PLAYER_H
#define PLAYER_H

#include <Box2D/Box2D.h>


/** \defgroup modulePlayer module de getsion du jouer(l'oiseau)
 *
 * \brief Un joueur est un corps physique box2D soumis à la gravité. 
 * cette classe permet de regouper les differents composants physique permettant de contrôler les mouvements du joueur
 */
  
class Player {
    public:
        /** @brief Constructeur par défaut de la classe Player: 
         * initialise la position initiale "in air" car le jouer commence en plein
         * */
        Player();
        
         /** @brief Inits le player et  l'ajoute aux monde physiques box2D world
         * autrement dit, c'est avec l'init qu'On commence à appliquer les contraintes physiques+gravité
         * */
        void initPlayer(b2World *w);


    /**
     * @brief Accesseur : permet de recuperer la position acutelle de joueur
     * \return b2Vec2
     */
        const b2Vec2& getPosition() const;

    /**
     * @brief Accesseur : permet de recuperer la vitesse acutelle de joueur
     * \return b2Vec2
     */
        const b2Vec2& getVelocity() const;

        void applyForce(b2Vec2 force);
        void setPosition(b2Vec2 pos, float32 angle);
        b2Body *playerBody;

    /**
     * @brief permet de savoir si le joueur est en plein air
     * \return bool
     */
        bool isInAir;

        void dive();

        void wake();
        void updateMovement();

    /**
     * @brief fonction qui commence le conact avec le terrain
     * isInAir est mis à false
     */
        void startContact();

    /**
     * @brief fonction qui termine le conact avec le terrain et remet le joueur en air
     * isInAir est mis à ture
     */
        void endContact();
        ~Player();

    private:
        
        b2World *world;
            
};

#endif
