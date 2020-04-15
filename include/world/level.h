#ifndef level_h
#define level_h

#include "world/squares/wall.h"
#include "world/squares/empty.h"
#include "world/squares/door.h"
#include "tools/fastrandom.h"
#include <set>
#include <map>

class Level {
public:
    Level();
    Level(int width, int height);
    ~Level();

    // Initialisation
    void randomGenerate();
    void generateStartRoom();
    void newLevel(Direction dir);
    void setPlayer(Player* p);
    void initPlayer();
    void initPlayer(Direction dir);

    // Game updates
    void setNeighbour(Direction d, Level* l);
    void newProjectile(Square* start, Direction dir);
    void removeProjectile(Projectile* p);
    void removeEnemy(Enemy* e);
    void updateEnemies();
    void updateProjectiles();

    // Getters
    Square* getSquareDir(Square* s, Direction dir);
    Square* getSquare(int x, int y);

    // Visuals
    void print(); //normal output
    void draw(); //ncurses: todo

private:
    Square*** board;
    FastRandom randgen;
    int height, width;
    int doorx, doory;

    std::set<Projectile*> projectiles;
    std::set<Enemy*> enemies;
    Player* player;
    std::map<Direction, Level*> neighbours;
};

#endif
