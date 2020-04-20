#include "tools/pathfind.h"
#include "world/level.h"
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include "tools/distance.h"
#include "entities/projectiles/projectile.h"
#include <chrono>

PathFind::PathFind() {}

PathFind::PathFind(Level* l) {
    lvl = l;
    bypassLockout = false;
}

PathFind::~PathFind() {}

struct FringeItem {
    FringeItem(Square* _s, double _bestDst) {
        s = _s;
        bestDst = _bestDst;
    }
    Square* s;
    double bestDst;
};
struct FringeCmp {
    bool operator()(const FringeItem& lhs, const FringeItem& rhs) {
        return lhs.bestDst > rhs.bestDst; // Low first
    }
};

Direction PathFind::AStar(Square* curPos) {
    //TODO: membervariables voor performance
    std::priority_queue<FringeItem,std::vector<FringeItem>,FringeCmp> q;
    std::set<Square*> visited({curPos});
    std::set<Square*> fringe;
    std::map<Square*, Direction> originalDir;
    std::map<Square*, int> distances;

    // Keep track of direct neighbours so that best first step can be selected
    for(int d = DIR_UP; d <= DIR_RIGHT; d++) {
        Square* directNeighbour = lvl->getSquareDir(curPos, static_cast<Direction>(d));
        if(directNeighbour->type() != SQUARE_FLOOR) continue;
        EmptySquare* es = dynamic_cast<EmptySquare*>(directNeighbour);
        if(es->getEnemy() != 0) continue; // Already occupied

        originalDir[directNeighbour] = static_cast<Direction>(d);
        distances[directNeighbour] = 1;
        q.push(FringeItem(directNeighbour,1));
        fringe.insert(directNeighbour);
    }

    while(!q.empty()) { // Dijkstra
        Square* cur = q.top().s;
        visited.insert(cur);

        for(int d = DIR_UP; d <= DIR_RIGHT; d++) {
            Square* neighbour = lvl->getSquareDir(cur, static_cast<Direction>(d));
            if(neighbour == 0) continue;
            if(neighbour->type() != SQUARE_FLOOR) continue;
            if(visited.find(neighbour) == visited.end()) {
                if(dynamic_cast<EmptySquare*>(cur)->getPlayer() != 0) {
                    return originalDir[cur];
                }
                // Update if new distance is smaller
                if( distances.find(neighbour) == distances.end() ||
                    (distances.find(neighbour) != distances.end() &&
                    distances[cur] + 1 < distances[neighbour])
                ){
                    distances[neighbour] = distances[cur]+1;
                    originalDir[neighbour] = originalDir[cur];
                }

                if(fringe.find(neighbour) == fringe.end()) {
                    q.push( FringeItem(neighbour,distances[neighbour] +
                            dist(neighbour, lvl->getPlayer()->getSquare())));
                    fringe.insert(neighbour);
                }
            }
        }
        fringe.erase(cur);
        q.pop();
    }
    //Shouldn't happen
    return DIR_UP;
}

Direction PathFind::dodgeProjectile(Square* curPos, Projectile* p) {
    bypassLockout = true; // Move immediately
    // If we can move out of the way, do so
    auto dirs = perpendiculars(p->getDirection());
    Square* s1 = lvl->getSquareDir(curPos, dirs.first);
    Square* s2 = lvl->getSquareDir(curPos, dirs.second);
    double option1Dst = dist(p->getSquare(), s1);
    double option2Dst = dist(p->getSquare(), s2);
    bool option1 = (s1 != 0) && (s1->type() == SQUARE_FLOOR);
    bool option2 = (s2 != 0) && (s2->type() == SQUARE_FLOOR);

    if(option1) {
        if(!option2 || (option2 && option1Dst > option2Dst)) { return dirs.first; }
    }
    if(option2) {
        if(!option1 || (option1 && option2Dst > option1Dst)) { return dirs.second; }
    }
    if(option1 && option2 && option1Dst == option2Dst) {
        return (rng.getLong()%2 == 0) ? dirs.first : dirs.second;
    }
    
    return opposite_dir(p->getDirection());
}

Projectile* PathFind::findCloseProjectile(Square* curPos) {
    auto pjs = lvl->getProjectiles();
    if(pjs->empty()) return 0;
    else {
        for(auto &i : *pjs) {
            if(dist(i->getSquare(), curPos) < MINDIST_PROJ) {
                return i;
            }
        }
    }
    return 0;
}

Action PathFind::getNextStep(Square* curPos) {
    if( rng.getDouble() < DODGE_CHANCE ) {
        Projectile* tmp = findCloseProjectile(curPos);
        if(tmp != 0) {
            Direction dodge = dodgeProjectile(curPos, tmp);
            return static_cast<Action>(dodge);
        }
    }

    if(dist(curPos, lvl->getPlayer()->getSquare()) > SEARCH_DST) {
        return ACTION_NONE;
        return static_cast<Action>(rng.getLong()%(ACTION_NONE+1));
    }
    else {
        Direction d = AStar(curPos);
        return ACTION_NONE;
        return static_cast<Action>(d);
    }
}
