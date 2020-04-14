#ifndef level_h
#define level_h

#include "world/squares/square.h"

class Level {
public:
    Level();
    Level(int width, int height);
    ~Level();
private:
    Square** board;
};

#endif
