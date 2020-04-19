#include "tools/pathfind.h"
#include "world/level.h"
#include <iostream>
#include <vector>
#include "tools/distance.h"

PathFind::PathFind() {}

PathFind::PathFind(Level* l) {
    lvl = l;
}

PathFind::~PathFind() {}

PathFind::BFS() {
    std::queue<Square*> q;
    std::set<Square*> visited({curPos});
    std::map<Square*, Direction> originalDir;
    std::map<Square*, int> distances;

    // Keep track of direct neighbours so that best first step can be selected
    for(int d = DIR_UP; d <= DIR_RIGHT; d++) {
        Square* directNeighbour = lvl->getSquareDir(curPos, static_cast<Direction>(d));
        if(directNeighbour == 0) continue;
        EmptySquare* es = consider(directNeighbour, &visited);
        if(es != 0) {
            // Already occupied
            if(es->getEnemy() != 0) continue;
            // Possibilty of dodging projectiles
            if(es->getProjectile() != 0) {
                double t = rng.getDouble();
                std::cout << t << std::endl;
                if(t < DODGE_CHANCE)  {
                    std::cout << "dodge@!" << std::endl;
                    continue;
                }
            }
            if(es != 0) {
                originalDir[directNeighbour] = static_cast<Direction>(d);
                visited.insert(directNeighbour);
                q.push(directNeighbour);
                distances[directNeighbour] = 1;
            }
        }
    }

    while(!q.empty()) { // BFS
        if(dynamic_cast<EmptySquare*>(q.front())->getPlayer() != 0) {
            return originalDir[q.front()];
        }

        for(int d = DIR_UP; d <= DIR_RIGHT; d++) {
            Square* neighbour = lvl->getSquareDir(q.front(), static_cast<Direction>(d));
            if(neighbour == 0) continue;
            if(es != 0) {
                visited.insert(es);
                q.push(es);
                originalDir[es] = originalDir[q.front()];
                distances[es] = distances[q.front()]+1;
            }
        }
        q.pop();
    }
    // Couldn't find player
    return -1;
}

Direction PathFind::getNextStep(Square* curPos) {
    if(dist(lvl->getPlayer()->getSquare(), curPos) < 15) {
        return (Direction)(rng.getLong()%(int)DIR_RIGHT+1);
    }
}
