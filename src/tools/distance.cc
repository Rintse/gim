#include "tools/distance.h"
#include "world/squares/square.h"


double dist(int x1, int y1, int x2, int y2) {
    return sqrt( ((x1-x2)*(x1-x2)) + ((y1-y2)*(y1-y2)) );
}

double dist(Square* s1, Square* s2) {
    return sqrt(    ((s1->getX()-s2->getX()) * (s1->getX()-s2->getX())) +
                    ((s1->getY()-s2->getY()) * (s1->getY()-s2->getY())) );
}
