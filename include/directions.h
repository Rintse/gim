#ifndef directions_h
#define directions_h

#define NUM_DIRECTIONS 4

enum Direction {
   UP,
   LEFT,
   DOWN,
   RIGHT
};

Direction opposite(Direction dir);

#endif
