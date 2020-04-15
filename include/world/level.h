#ifndef level_h
#define level_h

#include "world/squares/wall.h"
#include "world/squares/empty.h"
#include "world/squares/door.h"
#include "tools/fastrandom.h"
#include <set>
#include <map>

class Game;

class Level {
public:
    Level();
    Level(int w, int h, Game* g);
    ~Level();

    // Initialisation
    void randomGenerate();
    void generateStartRoom();
    Level* newLevel(Direction dir);
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
    void switchLevel(Direction dir);

    // Getters
    Square* getSquareDir(Square* s, Direction dir);
    Square* getSquare(int x, int y);

    // Visuals
    void print(); //normal output
    void draw(); //ncurses: todo

private:
    Square*** board;
    int height, width;
    int doorx, doory;
    Square* lastSquare;

    std::set<Projectile*> projectiles;
    std::set<Enemy*> enemies;
    Player* player;
    std::map<Direction, Level*> neighbours;
    Game* game;
};

#endif
