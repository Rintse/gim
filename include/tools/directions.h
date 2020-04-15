#ifndef directions_h
#define directions_h

#define NUM_DIRECTIONS 4

enum Direction {
   DIR_UP,
   DIR_LEFT,
   DIR_DOWN,
   DIR_RIGHT
};

Direction opposite_dir(Direction dir);

#endif
