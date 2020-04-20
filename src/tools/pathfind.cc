#include "tools/pathfind.h"
#include "world/level.h"
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include "tools/distance.h"

PathFind::PathFind() {}

PathFind::PathFind(Level* l) {
    lvl = l;
}

PathFind::~PathFind() {}

struct FringeItem {
    FringeItem(Square* _s, double _score) {
        s = _s;
        score = _score;
    }
    Square* s;
    double score;
};
struct FringeCmp {
    bool operator()(const FringeItem& lhs, const FringeItem& rhs)
    {
        return lhs.score < rhs.score;
    }
};

double PathFind::giveScore(Square* s, std::set<Square*> toFind) {
    // Penalise minimum distance from targets
    double minDst = std::numeric_limits<double>::infinity();
    for(auto &i : toFind) {
        double tdst = dist(i, s);
        if(tdst < minDst) {
            minDst = tdst;
        }
    }
    double score = -WEIGHT_PLAYER * minDst;

    // Reward distance from closes projectile
    std::set<Projectile*>* pjts = lvl->getProjectiles();
    if(pjts->empty()) return score;
    minDst = std::numeric_limits<double>::infinity();
    for(auto &i : *pjts) {
        double tdst = dist(i->getSquare(), s);
        if(tdst < minDst) {
            minDst = tdst;
        }
    }
    score += WEIGHT_PROJECTILE * minDst;
    return score;
}

std::map<Square*,double> PathFind::prioritySearch(std::set<Square*> toFind, int depth) {
    std::map<Square*,double> distances;
    for(auto& i : toFind) distances[i] = std::numeric_limits<double>::infinity();
    std::priority_queue<FringeItem,std::vector<FringeItem>,FringeCmp> q;
    Square* ps = lvl->getPlayer()->getSquare();
    q.push(FringeItem(ps, giveScore(ps, toFind)));
    distances[ps] = 0;

    while(!q.empty() && !toFind.empty()) { // BFS
        Square* cur = q.top().s;
        std::vector<FringeItem> toAdd;

        for(int d = DIR_UP; d <= DIR_RIGHT; d++) {
            Square* neighbour = lvl->getSquareDir(cur, static_cast<Direction>(d));
            if(neighbour->type() == SQUARE_FLOOR) { // Only consider empties
                distances[neighbour] = distances[cur]+1;
                if(toFind.find(neighbour) != toFind.end()) { // Found a toFind
                    toFind.erase(neighbour);
                }
                if(distances[neighbour] <= depth) { // Add neighbour to queue
                    toAdd.push_back(FringeItem(neighbour, giveScore(neighbour, toFind)));
                }
            }
        }

        q.pop();
        for(auto &i : toAdd) q.push(i);
    }
    // Couldn't find player
    return distances;
}

Action PathFind::getNextStep(Square* curPos) {
    // If euclidean distance too far, don't bother with search
    if(dist(lvl->getPlayer()->getSquare(), curPos) > SEARCH_DST) {
        return ACTION_NONE;
        return static_cast<Action>(rng.getLong()%(int)ACTION_MOVERIGHT+1);
    }
    else {
        std::map<Square*,Action> acts;
        std::set<Square*> toFind({ curPos });
        acts[curPos] = ACTION_NONE;

        for(int d = DIR_UP; d <= DIR_RIGHT; d++) {
            Square* tmp = lvl->getSquareDir(curPos, static_cast<Direction>(d));
            acts[tmp] = static_cast<Action>(d);
            if( tmp->type() == SQUARE_FLOOR &&
                dynamic_cast<EmptySquare*>(tmp)->getEnemy() == 0)
            {
                toFind.insert(tmp);
            }
        }
        // Find distances to all squares we can move to
        auto dsts = prioritySearch(toFind, SEARCH_DST+SEARCH_DELTA);
        // Determine best action
        std::vector<Action> best;
        double bestDst = std::numeric_limits<double>::infinity();
        for(auto & i : toFind) {
            std::cout << act_tostr(static_cast<Action>(acts[i])) << ": " <<
            dsts[i] << std::endl;
            if(dsts[i] == bestDst) {
                best.push_back(acts[i]);
            }
            else if(dsts[i] < bestDst) {
                best = {acts[i]};
            }
        }
        int idx = rng.getLong()%best.size();
        std::cout << "Final choice: " << act_tostr(best[idx]) << std::endl;
        return best[idx];
    }

    return ACTION_NONE;

}
