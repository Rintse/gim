#ifndef pathfind_h
#define pathfind_h

#define DODGE_CHANCE 0.3

#include "directions.h"
#include "fastrandom.h"

class Level;
class Square;

class BFS {
    public:
        BFS();
        BFS(Level* l);
        ~BFS();
        Direction getNextStep(Square* curPos);

    private:
        FastRandom rng;
        Level* lvl;
};

#endif
