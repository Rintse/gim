#ifndef directions_h
#define directions_h

#define NUM_DIRECTIONS 4

enum directions {
   UP,
   LEFT,
   DOWN,
   RIGHT
};

directions opposite(directions dir);

#endif
