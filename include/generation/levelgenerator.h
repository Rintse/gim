#ifndef level_gen_h
#define level_gen_h

#include "world/squares/square.h"
#include "tools/directions.h"
#include <iostream>
#include <vector>
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
    void advance(Direction d, int step, int x_max, int y_max) {
        switch(d) {
            case DIR_UP:
            if(y - step > 0)
                y -= step;
            break;

            case DIR_DOWN:
            if(y + step < y_max)
                y += step;
            break;

            case DIR_LEFT:
            if(x - step > 0)
                x -= step;
            break;

            case DIR_RIGHT:
            if(x + step < x_max)
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
        //CONSTRUCTION / INITIALIZATION
        LevelGenerator(int width, int height);
        ~LevelGenerator();
        void initBoard(int w, int h, Direction in_dir, int in_index,
                        Direction out_dir, int out_index);
        void initBoard(Level* l, int w, int h, Direction in_dir, int in_index, Direction out_dir, int out_index);

        //SETTER
        void setLevel(Level* l);

        //AUX BOARD FUNCTION
        void printCharBoard() const;

        //ROOM GENERATION
        Square*** startRoom(int w, int h, int room_door_row, int boss_door_column);
        Square*** bossRoom(int w, int h, pos door);
        Square*** randomRoom(int w, int h, int room_doory, FastRandom &r);
        Square*** cpeRoom(int d);
        Square*** testRoom(int d);

    private:
        //lEVEL INFO
        int width;
        int height;

        pos entrance;
        Direction in;

        pos exit;
        Direction out;

        char** board = NULL; //intermediate board representation
        Level* level;        //level this board will belong to
        FastRandom* rand;


        //PROCEDURAL DIFFICULTY / REWARDS
        std::vector<pos> power_positions; //where we like to place powerups
        std::vector<pos> enemy_positions; //where we like to place enemies

        int depth = 0;          //depth of the level we generate
        int target_mut;         //no. mutations we want
        int target_powers;      //no. powers we want

        int n_floor;            //no. floor tiles
        int n_mut = 0;          //no. mutations
        int enemy_permille;     //no. enemies we want per 1000 tiles
        int remain;             //no. opportunities for mutation are left

        //INITIALIZATION
        pos generateDoors(Direction d, int i) const;

        //AUX BOARD FUNCTIONS
        int distanceToEdge(Direction d, pos p);
        void clearChar();
        void deleteCharBoard();

        //SQUARE PLACEMENT
        void spawnEnemy(Square* s);
        void spawnHeart(Square* s);
        void spawnFBullet(Square* s);
        void placePowers(Square *** b);
        void placeEnemies(Square *** b);
        void placeFloor(int x, int y, bool critical = false);


        //CHAR -> SQUARE BOARD CONVERSION
        Square* createSquare(char c, int x, int y);
        Square*** createBoard();

        //PATH GENERATION
        int mutatePath(Direction to, int max, double mut_rate, pos start);
        void straightPath(Direction d, pos start, pos end, int length, bool power);
        void straightPath(Direction d, pos start, int length, bool power);
        pos uPath(Direction d, Direction turn_d, int length, int turn_length, pos start);

        //PROCEDURAL DIFFICULTY
        void setDifficulty();
};

#endif
