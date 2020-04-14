#include "directions.h"

directions opposite(directions dir) {
    return (directions) (((int)dir + 2) % 4);
}
