#ifndef pathfind_h
#define pathfind_h

#define WEIGHT_PLAYER 2
#define WEIGHT_PROJECTILE 5
#define SEARCH_DST 15 // Minimum distance before prioritySearchign
#define SEARCH_DELTA 5 // Extra search depth to account for obstacles

#include "tools/directions.h"
#include "tools/actions.h"
#include "fastrandom.h"
#include <set>
#include <map>

class Level;
class Square;
class EmptySquare;

class PathFind {
    public:
        PathFind();
        PathFind(Level* l);
        ~PathFind();
        Direction AStar(Square* curPos);
        Action getNextStep(Square* curPos);


    private:
        FastRandom rng;
        Level* lvl;
};

#endif
