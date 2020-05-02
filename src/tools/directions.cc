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

std::pair<Direction,Direction> perpendiculars(Direction dir) {
    switch (dir) {
        case DIR_UP: case DIR_DOWN: return std::make_pair(DIR_LEFT, DIR_RIGHT);
        default: case DIR_LEFT: case DIR_RIGHT: return std::make_pair(DIR_UP, DIR_DOWN);
    }
}

//return the left perpendicular direction relative to 'd'
Direction left_dir(Direction d) {
    switch(d) {
        case DIR_UP:
            return DIR_LEFT;
        case DIR_DOWN:
            return DIR_RIGHT;
        case DIR_LEFT:
            return DIR_DOWN;
        case DIR_RIGHT:
            return DIR_UP;
    }
    return DIR_UP;
}

//return the left perpendicular direction relative to 'd'
Direction right_dir(Direction d) {
    switch(d) {
        case DIR_UP:
            return DIR_RIGHT;
        case DIR_DOWN:
            return DIR_LEFT;
        case DIR_LEFT:
            return DIR_UP;
        case DIR_RIGHT:
            return DIR_DOWN;
    }
    return DIR_UP;
}

bool operator ==(Direction l, Direction r)
{
    return static_cast<Direction> (
        static_cast<std::underlying_type<Direction>::type>(l) ==
        static_cast<std::underlying_type<Direction>::type>(r)
    );
}
