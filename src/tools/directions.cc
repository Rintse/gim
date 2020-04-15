#include "tools/directions.h"

Direction opposite_dir(Direction dir) {
    return (Direction) (((int)dir + 2) % 4);
}

std::string dir_tostr(Direction dir) {
    switch (dir) {
        case DIR_UP: return "up";
        case DIR_LEFT: return "left";
        case DIR_DOWN: return "down";
        default: case DIR_RIGHT: return "right";
    }
}
