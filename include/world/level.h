#ifndef level_h
#define level_h

#include "world/squares/wall.h"
#include "world/squares/empty.h"
#include "fastrandom.h"
#include <list>

class Level {
public:
    Level();
    Level(int width, int height);
    ~Level();

    void randomGenerate();
    Square* getSquare(int x, int y);
    void print(); //normal output
    void draw(); //ncurses: todo
private:
    Square*** board;
    FastRandom randgen;
    int height, width;
    std::list<Entity> entities;
    std::list<NPC> npcs;
};

#endif
