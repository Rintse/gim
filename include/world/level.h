#ifndef level_h
#define level_h

#include "world/squares/wall.h"
#include "world/squares/empty.h"
#include "fastrandom.h"

class Level {
public:
    Level();
    Level(int width, int height);
    ~Level();

    void randomGenerate();
    Square* getSquare(int x, int y);
private:
    Square*** board;
    FastRandom randgen;
    int height, width;
};

#endif
