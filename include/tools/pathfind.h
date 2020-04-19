#ifndef pathfind_h
#define pathfind_h

#define DODGE_CHANCE 1

#include "directions.h"
#include "fastrandom.h"
#include <set>

class Level;
class Square;
class EmptySquare;

class BFS {
    public:
        BFS();
        BFS(Level* l);
        ~BFS();
        Direction getNextStep(Square* curPos);
        EmptySquare* consider(Square* s, std::set<Square*>* visited);

    private:
        FastRandom rng;
        Level* lvl;
};

#endif
