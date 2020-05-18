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

#define SIGHT_DEGRATION 5

class Level {
public:
    Level();
    Level(int w, int h, Game* g, int vd, int d = 0);
    ~Level();

    // Initialisation
    void setRoom(Square*** b);
    Level* newLevel(Direction dir);
    void setPlayer(Player* p);
    void initPlayer();
    void initPlayer(Direction dir);
    void spawnEnemy(Square* s);
    void spawnHeart(Square* s);

    // Game updates
    void setNeighbour(Direction d, Level* l);
    void newProjectile(Projectile* p);
    void removeProjectile(Projectile* p);
    void removeEnemy(Enemy* e);
    void updateEnemies();
    void updateProjectiles();
    void updateGeorge();
    void switchLevel(Direction dir);
    void signalGameOver(bool won);
    double BFSdist(Square* from, Square* to);
    void hurtGeorge();
    void setGeorge();

    // Getters
    Square* getSquareDir(Square* s, Direction dir);
    Square* getSquare(int x, int y);
    Player* getPlayer();
    George* getGeorge();
    std::set<Projectile*>* getProjectiles();
    int getWidth() const;
    int getHeight() const;
    int getViewDistance() const;
    int getDepth() const;
    void addEnemy(Enemy* e);
    bool noEnemies();

private:
    Square*** board;
    int height, width;
    int doorx, doory;
    int viewDistance;
    int depth;

    std::set<Projectile*> projectiles;
    std::set<Enemy*> enemies;
    Player* player;
    George* george;
    std::map<Direction, Level*> neighbours;
    Game* game;

};

#endif
