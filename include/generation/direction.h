#ifndef dir_h
#define dir_h
/**
*   Enum describing cardinal directions
*   Bitmask representation to store multiple directions
*   (Used in LevelGenerator to denote mutations that work in multiple directions)
*/

enum DIR_MASK : uint8_t {
    NONE    = 0,
    UP      = (1u << 0),
    DOWN    = (1u << 1),
    LEFT    = (1u << 2),
    RIGHT   = (1u << 3)
};

//return DIR_MASK representing the oposite direction (single dir only)
inline DIR_MASK reverse(DIR_MASK d) {
    switch(d) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        default:
            return d;
    }
}

inline DIR_MASK turnLeft(DIR_MASK d) {
    switch(d) {
        case UP:
            return LEFT;
        case DOWN:
            return RIGHT;
        case LEFT:
            return DOWN;
        case RIGHT:
            return UP;
        default:
            return d;
    }
}

inline DIR_MASK turnRight(DIR_MASK d) {
    switch(d) {
        case UP:
            return RIGHT;
        case DOWN:
            return LEFT;
        case LEFT:
            return UP;
        case RIGHT:
            return DOWN;
        default:
            return d;
    }
}

inline bool operator ==(DIR_MASK l, DIR_MASK r)
{
    return static_cast<DIR_MASK> (
        static_cast<std::underlying_type<DIR_MASK>::type>(l) ==
        static_cast<std::underlying_type<DIR_MASK>::type>(r)
    );
}

inline DIR_MASK operator |(DIR_MASK l, DIR_MASK r)
{
    return static_cast<DIR_MASK> (
        static_cast<std::underlying_type<DIR_MASK>::type>(l) |
        static_cast<std::underlying_type<DIR_MASK>::type>(r)
    );
}

inline DIR_MASK operator &(DIR_MASK l, DIR_MASK r)
{
    return static_cast<DIR_MASK> (
        static_cast<std::underlying_type<DIR_MASK>::type>(l) &
        static_cast<std::underlying_type<DIR_MASK>::type>(r)
    );
}

inline DIR_MASK operator ~(DIR_MASK r)
{
    return static_cast<DIR_MASK> (
        ~static_cast<std::underlying_type<DIR_MASK>::type>(r)
    );
}

inline DIR_MASK& operator |=(DIR_MASK &l, DIR_MASK r)
{
    l = static_cast<DIR_MASK> (
        static_cast<std::underlying_type<DIR_MASK>::type>(l) |
        static_cast<std::underlying_type<DIR_MASK>::type>(r)
    );

    return l;
}

inline DIR_MASK& operator &=(DIR_MASK &l, DIR_MASK r)
{
    l = static_cast<DIR_MASK> (
        static_cast<std::underlying_type<DIR_MASK>::type>(l) &
        static_cast<std::underlying_type<DIR_MASK>::type>(r)
    );

    return l;
}
#endif
