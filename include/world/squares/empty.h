#ifndef empty_h
#define empty_h

#include "world/squares/square.h"

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
        // Setters
        void setPlayer(Player* p);
        void setProjectile(Projectile* p);
        void setEnemy(Enemy* e);
        void setGeorgepart(GeorgePart* g);
        bool hasHeart();
        void setHeart(bool h);

    private:
        bool heart;
        Player* player;
        Projectile* projectile;
        Enemy* enemy;
        GeorgePart* georgepart;
};

#endif
