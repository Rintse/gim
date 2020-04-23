#ifndef level_gen_h
#define level_gen_h

#include "world/squares/square.h"
#include "generation/direction.h"
#include "tools/fastrandom.h"
#include <iostream>
// class that generates game boards
// methods allocate the board on the heap and pass a reference to be given to a Level
//

struct pos {
    int row;
    int col;

    void advance(DIR_MASK d, int step) {
        switch(d) {
            case UP:
            this->row -= step;
            break;

            case DOWN:
            this->row += step;
            break;

            case LEFT:
            this->col -= step;
            break;

            case RIGHT:
            this->col += step;
            break;

            default:
                std::cerr << "pos::advance: Invalid direction" << std::endl;
            break;
        }
    }

    pos& operator =(const pos &r)
    {
        row = r.row;
        col = r.col;

        return *this;
    }
};

class LevelGenerator {
    public:
        LevelGenerator(int width, int height);
        void printCharBoard() const;
        Square*** startRoom(int width, int height);
        Square*** bossRoom(int width, int height);
        Square*** emptyRoom(int width, int height);

        /**
        *   Critical Path Evolution Room generation
        *   Generates a maze-like room by starting with a simple 'critical path'
        *   and mutating it
        *   @param w        Level dimensions
                   h
        *   @param mut          Mutation rate, range [0.0 .. 1.0].
                                Denotes how likely an arbitrary square is to be mutated
                                Increases level complexity
        *   @param path_width   Sets a standardized width for generated path, also
                                (influences how far apart mutations may occur?)
        *   @return             Pointer to a board on the heap, to be passed to a Level
        */
        Square*** cpeRoom();

    private:
        int width;
        int height;
        pos entrance;
        DIR_MASK in;
        pos exit;
        DIR_MASK out;
        double mut;
        char** board = NULL;
        FastRandom randoom;

        int distanceToEdge(DIR_MASK d, pos p);
        pos generateDoors(DIR_MASK d, int i) const;
        void initBoard(int w, int h, DIR_MASK in_dir, int in_index,
                                     DIR_MASK out_dir, int out_index);

        pos mutatePath(DIR_MASK to, int max, int width, double mut_rate, pos start);
        //starts type of path on location (x,y) into direction
        void straightPath(DIR_MASK d, int length, int width, double mut_rate, pos start);
        void straightUntil(DIR_MASK d, int width, double mut_rate, pos start, pos end);
        pos uPath(DIR_MASK d, DIR_MASK turn_d, int length, int turn_length, int width, double mut_rate, pos start);
};

#endif
