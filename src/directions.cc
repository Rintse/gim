#include "directions.h"

Direction opposite(Direction dir) {
    return (Direction) (((int)dir + 2) % 4);
}
