#ifndef level_h
#define level_h

#include "world/squares/wall.h"
#include "world/squares/empty.h"
#include "world/squares/door.h"
#include "tools/fastrandom.h"
#include "entities/george/george.h"
#include <set>
#include <map>

class Game;

class Level {
public:
    Level();
    Level(int w, int h, Game* g);
    ~Level();

    // Initialisation
    void generateBossRoom();
    void generateStartRoom();
    void generateRandomRoom();
    Level* newLevel(Direction dir);
    void setPlayer(Player* p);
    void initPlayer();
    void initPlayer(Direction dir);
    void createBossRoom();
    void spawnEnemy(Square* s);

    // Game updates
    void setNeighbour(Direction d, Level* l);
    void newProjectile(Projectile* p);
    void removeProjectile(Projectile* p);
    void removeEnemy(Enemy* e);
    void updateEnemies();
    void updateProjectiles();
    void updateGeorge();
    void switchLevel(Direction dir);
    void signalGameOver();
    double BFSdist(Square* from, Square* to);
    void hurtGeorge();

    // Getters
    Square* getSquareDir(Square* s, Direction dir);
    Square* getSquare(int x, int y);
    Player* getPlayer();
    std::set<Projectile*>* getProjectiles();
    int getWidth();
    int getHeight();
    bool noEnemies();

private:
    void setGeorge();

    Square*** board;
    int height, width;
    int doorx, doory;
    Square* lastSquare; //TODO:delete?

    std::set<Projectile*> projectiles;
    std::set<Enemy*> enemies;
    Player* player;
    George* george;
    std::map<Direction, Level*> neighbours;
    Game* game;

};

#endif
