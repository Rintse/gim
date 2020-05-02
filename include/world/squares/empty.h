#ifndef empty_h
#define empty_h

#include "world/squares/square.h"
#include "entities/powerups/powerup.h"

class EmptySquare : public Square {
    public:
        EmptySquare(int _x, int _y);
        ~EmptySquare();

        SquareType type();
        char token();
        // Getters
        Player* getPlayer();
        Projectile* getProjectile();
        Enemy* getEnemy();
        GeorgePart* getGeorgepart();
        Powerup* getPowerup();
        // Setters
        void setPlayer(Player* p);
        void setProjectile(Projectile* p);
        void setEnemy(Enemy* e);
        void setGeorgepart(GeorgePart* g);
        void setPowerup(Powerup* p);


    private:
        Powerup* pu;
        Player* player;
        Projectile* projectile;
        Enemy* enemy;
        GeorgePart* georgepart;
};

#endif
