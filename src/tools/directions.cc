#include "tools/directions.h"

Direction opposite_dir(Direction dir) {
    return (Direction) (((int)dir + 2) % 4);
}
