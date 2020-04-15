#ifndef square_h
#define square_h

#include "directions.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"

enum SquareType {
    SQUARE_FLOOR, SQUARE_DOOR, SQUARE_WALL
};

class Square {
    public:
        Square() {}
        virtual ~Square() {}
        virtual char token() = 0;
        virtual SquareType type() = 0;
        int getX() { return x; };
        int getY() { return y; };
        Player* getPlayer() { return player; }
        Projectile* getProjectile() { return projectile; }
        Enemy* getEnemey() { return enemy; }
        void setPlayer(Player* p) { player = p; }
        void setProjectile(Projectile *p) { projectile = p }
        void setEnemey(Enemy* e) { enemy = e; }

    private:
        Player* player;
        Projectile* projectile;
        Enemy* enemy;
        int x,y;
};

#endif
