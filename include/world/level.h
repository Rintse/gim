#ifndef level_h
#define level_h

#include "world/squares/wall.h"
#include "world/squares/empty.h"
#include "world/squares/door.h"
#include "fastrandom.h"
#include <set>

class Level {
public:
    Level();
    Level(int width, int height);
    ~Level();

    void randomGenerate();
    void generateStartRoom();
    Square* getSquareDir(Square* s, Direction dir);
    Square* getSquare(int x, int y);
    void print(); //normal output
    void draw(); //ncurses: todo
    void killEnemy(Enemy* e);
    void updateEnemies();
    void updateProjectiles();
private:
    Square*** board;
    FastRandom randgen;
    int height, width;
    int doorx, doory;

    std::set<Projectile*> projectiles;
    std::set<Enemy*> enemies;
    Player* player;
    Level* left, * right;
};

#endif
