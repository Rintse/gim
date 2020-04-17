#include "tools/pathfind.h"
#include "world/level.h"
#include <set>
#include <queue>
#include <map>

BFS::BFS() {}

BFS::BFS(Level* l) {
    lvl = l;
}

BFS::~BFS() {}

Direction BFS::getNextStep(Square* curPos) {
    bool foundPlayer = false;
    std::queue<Square*> q;
    std::set<Square*> visited({curPos});
    std::map<Square*, Direction> originalDir;

    // Keep track of direct neighbours so that best first step can be selected
    std::map<Square*,Direction> orginalDir;
    for(int d = DIR_UP; d <= DIR_RIGHT; d++) {
        Square* directNeighbour = lvl->getSquareDir(q.back(), static_cast<Direction>(d));
        originalDir[directNeighbour] = static_cast<Direction>(d);
        visited.insert(directNeighbour);
        q.push(directNeighbour);
    }

    while(!q.empty()) { // BFS
        if(q.back()->getPlayer() == 0) { foundPlayer = true; break; }
        for(int d = DIR_UP; d <= DIR_RIGHT; d++) {
            Square* neighbour = lvl->getSquareDir(q.back(), static_cast<Direction>(d));
            if(neighbour == 0) continue;
            if(neighbour->type() == SQUARE_FLOOR) {
                // Already occupied
                if(neighbour->getEnemy() != 0) continue;
                // Possibilty of dodging projectiles
                if(neighbour->getProjectile() != 0) {
                    double t = (double)rng.getLong() / rng.getMax();
                    if(t < DODGE_CHANCE) {
                        continue;
                    }
                }
                if(visited.find(neighbour) == visited.end()) {
                    visited.insert(neighbour);
                    q.push(neighbour);
                    originalDir[neighbour] = originalDir[q.back()];
                }
            }
        }
        q.pop();
    }

    if(foundPlayer) return originalDir[q.back()];
    else return (Direction)(rng.getLong()%(int)DIR_RIGHT+1);
}
