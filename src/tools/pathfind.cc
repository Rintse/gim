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

Action PathFind::getNextStep(Square* curPos) {
    return ACTION_NONE;
}
