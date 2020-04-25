#ifndef level_gen_h
#define level_gen_h

#include "world/squares/square.h"
#include "tools/directions.h"
#include <iostream>
// class that generates game boards
// methods allocate the board on the heap and pass a reference to be given to a Level
//

struct pos {
    int row;
    int col;

    void advance(Direction d, int step) {
        switch(d) {
            case DIR_UP:
            this->row -= step;
            break;

            case DIR_DOWN:
            this->row += step;
            break;

            case DIR_LEFT:
            this->col -= step;
            break;

            case DIR_RIGHT:
            this->col += step;
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
        Direction in;
        pos exit;
        Direction out;
        double mut;
        char** board = NULL;
        FastRandom randoom;

        int distanceToEdge(Direction d, pos p);
        pos generateDoors(Direction d, int i) const;
        void initBoard(int w, int h, Direction in_dir, int in_index,
                                     Direction out_dir, int out_index);

        pos mutatePath(Direction to, int max, int width, double mut_rate, pos start);
        //starts type of path on location (x,y) into direction
        void straightPath(Direction d, int length, int width, double mut_rate, pos start);
        void straightUntil(Direction d, int width, double mut_rate, pos start, pos end);
        pos uPath(Direction d, Direction turn_d, int length, int turn_length, int width, double mut_rate, pos start);
};

#endif
