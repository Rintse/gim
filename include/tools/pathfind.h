#ifndef pathfind_h
#define pathfind_h

#define SEARCH_DST 15 // Minimum distance before prioritySearchign
#define MINDIST_PROJ 3
#define DODGE_CHANCE 0.4

#include "tools/directions.h"
#include "tools/actions.h"
#include "fastrandom.h"
#include <set>
#include <map>

class Level;
class Square;
class EmptySquare;
class Projectile;

class PathFind {
    public:
        PathFind();
        PathFind(Level* l);
        ~PathFind();
        Direction AStar(Square* curPos);
        Action getNextStep(Square* curPos);
        Direction dodgeProjectile(Square* curPos, Projectile* p);
        Projectile* findCloseProjectile(Square* curPos);

        bool bypassLockout;

    private:
        FastRandom rng;
        Level* lvl;
};

#endif
