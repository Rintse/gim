#ifndef directions_h
#define directions_h

#include <string>
#include <utility>

#define NUM_DIRECTIONS 4

enum Direction {
   DIR_UP,
   DIR_LEFT,
   DIR_DOWN,
   DIR_RIGHT
};

std::string dir_tostr(Direction dir);

Direction opposite_dir(Direction dir);

Direction left_dir(Direction d);

Direction right_dir(Direction d);

std::pair<Direction,Direction> perpendiculars(Direction dir);

bool operator ==(Direction l, Direction r);

Direction operator |(Direction l, Direction r);

Direction operator &(Direction l, Direction r);

Direction operator ~(Direction r);

Direction& operator |=(Direction &l, Direction r);

Direction& operator &=(Direction &l, Direction r);


#endif
