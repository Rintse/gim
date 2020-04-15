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
        Square(int _x, int _y) {
            player = 0;
            projectile = 0;
            enemy = 0;
            x = _x;
            y = _y;
        }
        virtual ~Square() {}
        virtual char token() = 0;
        virtual SquareType type() = 0;
        int getX() { return x; };
        int getY() { return y; };
        Player* getPlayer() { return player; }
        Projectile* getProjectile() { return projectile; }
        Enemy* getEnemy() { return enemy; }
        void setPlayer(Player* p) { player = p; }
        void setProjectile(Projectile *p) { projectile = p; }
        void setEnemy(Enemy* e) { enemy = e; }

    protected:
        Player* player;
        Projectile* projectile;
        Enemy* enemy;
        int x,y;
};

#endif
