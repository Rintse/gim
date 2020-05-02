#ifndef level_gen_h
#define level_gen_h

#include "world/squares/square.h"
#include "tools/directions.h"
#include <iostream>
// class that generates game boards
// methods allocate the board on the heap and pass a reference to be given to a Level
//

struct pos {
    int x;
    int y;

    void advance(Direction d, int step) {
        switch(d) {
            case DIR_UP:
            y -= step;
            break;

            case DIR_DOWN:
            y += step;
            break;

            case DIR_LEFT:
            x -= step;
            break;

            case DIR_RIGHT:
            x += step;
            break;
        }
    }

    pos& operator =(const pos &r)
    {
        x = r.x;
        y = r.y;

        return *this;
    }
};

class LevelGenerator {
    public:
        LevelGenerator(int width, int height);
        void initBoard(int w, int h, Direction in_dir, int in_index,
                        Direction out_dir, int out_index);
        void initBoard(Level* l, int w, int h, Direction in_dir, int in_index,
                        Direction out_dir, int out_index);
        void setLevel(Level* l);

        void printCharBoard() const;
        Square*** randomRoom(int w, int h, int room_doory, FastRandom &r);
        Square*** cpeRoom();
        Square*** cpeRoom(Direction in_dir, int in_offset, Direction out_dir, int out_offset);
        Square*** bossRoom(int w, int h, pos door);
        Square*** startRoom(int w, int h, int room_door_row, int boss_door_column);

    private:
        int width;
        int height;
        pos entrance;
        Direction in;
        pos exit;
        Direction out;
        double mut;
        char** board = NULL;
        Level* level;
        std::set<Enemy*> enemies;

        int distanceToEdge(Direction d, pos p);
        pos generateDoors(Direction d, int i) const;
        void clearChar();

        Square* createSquare(char c, int x, int y);
        void spawnEnemy(Square* s);
        void spawnHeart(Square* s);

        Square*** createBoard();

        pos mutatePath(Direction to, int max, int interval, double mut_rate, pos start);

        void straightPath(Direction d, int interval, double mut_rate, pos start, pos end);
        pos uPath(Direction d, Direction turn_d, int length, int turn_length, int interval,
                    double mut_rate, pos start);
};

#endif
