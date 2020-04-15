#ifndef directions_h
#define directions_h

#include <string>

#define NUM_DIRECTIONS 4

enum Direction {
   DIR_UP,
   DIR_LEFT,
   DIR_DOWN,
   DIR_RIGHT
};

std::string dir_tostr(Direction dir);

Direction opposite_dir(Direction dir);

#endif
