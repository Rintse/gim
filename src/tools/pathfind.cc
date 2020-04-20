#include "tools/pathfind.h"
#include "world/level.h"
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include "tools/distance.h"
#include <chrono>

PathFind::PathFind() {}

PathFind::PathFind(Level* l) {
    lvl = l;
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
                    distances[cur] + 1 < distances[neighbour]))
                {
                    distances[neighbour] = distances[cur]+1;
                    originalDir[neighbour] = originalDir[cur];
                }

                if(fringe.find(neighbour) == fringe.end()) {
                    q.push(FringeItem(neighbour,distances[neighbour] + dist(neighbour, lvl->getPlayer()->getSquare())));
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

Action PathFind::getNextStep(Square* curPos) {
    if(dist(curPos, lvl->getPlayer()->getSquare()) > SEARCH_DST) {
        return static_cast<Action>(rng.getLong()%(ACTION_NONE+1));
    }
    else {
        Direction d = AStar(curPos);
        return static_cast<Action>(d);
    }
}
