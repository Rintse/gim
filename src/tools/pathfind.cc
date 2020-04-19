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
        Square* directNeighbour = lvl->getSquareDir(curPos, static_cast<Direction>(d));
        if(directNeighbour->type() != SQUARE_FLOOR) continue;
        originalDir[directNeighbour] = static_cast<Direction>(d);
        visited.insert(directNeighbour);
        q.push(directNeighbour);
    }

    while(!q.empty()) { // BFS
        if(dynamic_cast<EmptySquare*>(q.back())->getPlayer() == 0) {
            foundPlayer = true; break;
        }
        for(int d = DIR_UP; d <= DIR_RIGHT; d++) {
            Square* neighbour = lvl->getSquareDir(q.back(), static_cast<Direction>(d));
            if(neighbour == 0) continue;
            if(neighbour->type() == SQUARE_FLOOR) {
                EmptySquare* tmp = dynamic_cast<EmptySquare*>(neighbour);
                // Already occupied
                if(tmp->getEnemy() != 0) continue;
                // Possibilty of dodging projectiles
                if(tmp->getProjectile() != 0) {
                    double t = rng.getDouble();
                    if(t < DODGE_CHANCE) continue;
                }
                if(visited.find(tmp) == visited.end()) {
                    visited.insert(tmp);
                    q.push(tmp);
                    originalDir[tmp] = originalDir[q.back()];
                }
            }
        }
        q.pop();
    }

    if(foundPlayer) return originalDir[q.back()];
    else return (Direction)(rng.getLong()%(int)DIR_RIGHT+1);
}
