#ifndef pathfind_h
#define pathfind_h

#define PLAYERWEIGHT 5
#define PROJECTILEWEIGHT 1
#define SCARED_DIST 5

#include "tools/directions.h"
#include "tools/actions.h"
#include "fastrandom.h"
#include <set>

class Level;
class Square;
class EmptySquare;

class PathFind {
    public:
        PathFind();
        PathFind(Level* l);
        ~PathFind();
        Action getNextStep(Square* curPos);

    private:
        FastRandom rng;
        Level* lvl;
};

#endif
