#include "generation/levelgenerator.h"
#include "world/squares/wall.h"
#include "world/squares/empty.h"
#include "world/squares/door.h"

#include <stdlib.h>


// 'I' IN
// 'O' OUT
//  0  EMPTY

//d: side of the board, the door is on
pos LevelGenerator::generateDoors(Direction d, int i) const {
    switch(d) {
        case DIR_UP:
            return {0, i};
        case DIR_DOWN:
            return {height-1,i};
        case DIR_LEFT:
            return {i, 0};
        case DIR_RIGHT:
            return {i, width-1};
    }
    return {0,0};
}

void LevelGenerator::initBoard(int w, int h,
                               Direction in_dir, int in_index,
                               Direction out_dir, int out_index)
{
    if(w <= 0 || h <= 0) {
        std::cerr << "LevelGenerator: Invalid board dimensions" << std::endl;
        return;
    }
    width = w; height = h;

    entrance = generateDoors(in_dir, in_index);
    exit = generateDoors(out_dir, out_index);

    in = in_dir;
    out = out_dir;

    if(board != NULL) { //TODO mogelijk resizen
        std::cerr << "LevelGenerator: Delete board" << std::endl;
        for(int i = 0; i < height; i++) {
            if(board[i] != NULL)
                delete[] board[i];
        }
        delete[] board;
    }
    std::cerr << "LevelGenerator: Allocate board" << std::endl;
    board = new char*[height];

    for(int i = 0; i < height; i++)
        board[i] = new char[width];

    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++) {
            if(i == entrance.row && j == entrance.col)
                board[i][j] = 'I';
            else if(i == exit.row && j == exit.col)
                board[i][j] = 'O';
            else //if(i > 0)
                board[i][j] = '-';
            // else
            //     board[i][j] = '1';
        }
    // srand(9);
    srand(time(NULL));
}

LevelGenerator::LevelGenerator(int w, int h) {
    initBoard(w, h, DIR_LEFT, h/2, DIR_RIGHT, h/2);
    mut = 0.3;
}

void LevelGenerator::printCharBoard() const {
    std::cerr << "LevelGenerator: Print board" << std::endl;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "=======================================================" << std::endl;
}

Square* createSquare(char c) {
    // switch(c) {
    //     case '-': return new
    //
    // }
    return NULL;
}

Square*** createBoard(int width, int height, char*** c_board) {
    Square*** board = new Square**[width];
    for(int i = 0; i < width; i++)
        board[i] = new Square*[height];

    for(int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
            board[i][j] = createSquare(*c_board[i][j]);

    return board;
}

Square*** LevelGenerator::bossRoom(int w, int h, pos door) {
    Square*** square_board = new Square**[h];

    for(int i = 0; i < h; i++) {
        square_board[i] = new Square*[w];

        for(int j = 0; j < w; j++) {
            // Edges
            if(i == 0 || j == 0 || i == h-1 || j == w-1) {
                // Door on bottom
                if(i == door.row && j == door.col)
                    square_board[i][j] = new DoorSquare(i,j,DIR_DOWN);
                else // Walls around the entire thing
                    square_board[i][j] = new WallSquare(i,j);
            }
            else {
                square_board[i][j] = new EmptySquare(i,j);
            }
        }
    }

    return square_board;
}

Square*** LevelGenerator::startRoom(int w, int h, int room_door_row, int boss_door_column) {
    Square*** square_board = new Square**[h];

    for(int i = 0; i < h; i++) {
        square_board[i] = new Square*[w];

        for(int j = 0; j < w; j++) {
            // Edges
            if(i == 0 || j == 0 || i == h-1 || j == w-1) {
                // Doors on top, left, right
                if( (i == 0 && j == boss_door_column) ||
                    ((j == 0 || j == w-1) && i == room_door_row) ) {
                    Direction dir;

                    if(j == 0)
                        dir = DIR_LEFT;
                    else if(j == h-1)
                        dir = DIR_RIGHT;
                    else
                        dir = DIR_UP;

                    square_board[i][j] = new DoorSquare(i,j,dir);
                }
                else { // Walls around the entire thing
                    square_board[i][j] = new WallSquare(i,j);
                }
            }
            // Hallway
            else if((j < boss_door_column-6 && i < room_door_row-6) ||
                    (j > boss_door_column+6 && i < room_door_row-6) ||
                    (j < boss_door_column-6 && i > room_door_row+6) ||
                    (j > boss_door_column+6 && i > room_door_row+6)) {

                square_board[i][j] = new WallSquare(i,j);
            }
            else {
                square_board[i][j] = new EmptySquare(i,j);
            }
        }
    }
    return square_board;
}

Square*** LevelGenerator::cpeRoom() {
    std::cerr << "LevelGenerator: cpeRoom start" << std::endl;
    //generate critical path
    char** board = new char*[width]; //chars to allow multiple changes to board

    //init
    for(int i = 0; i < width; i++) {
        board[i] = new char[height];
        for(int j = 0; j < height; j++)
            board[i][j] = 0;
    }

    pos walk = entrance;
    walk.advance(opposite_dir(in), 1);

    pos finish = exit;
    finish.advance(opposite_dir(out), 1);

    straightPath(opposite_dir(in), 2, 0.7, walk, finish);

    //TODO arbitrary starting position RL/UD: Z/N-shape random corners

    return NULL;
}

//No.  squares between p and edge d
int LevelGenerator::distanceToEdge(Direction d, pos p) {
    switch(d) {
        case DIR_UP:    return p.row;
        case DIR_DOWN:  return height-1-p.row;
        case DIR_LEFT:  return p.col;
        case DIR_RIGHT: return width-1-p.col;
    }
    return -1;
}

pos LevelGenerator::mutatePath(Direction to, int parent_remainder, int width, double mut_rate, pos start) {
    double r = rand();
    double max = RAND_MAX;
    double c = r/max;

    if( c < mut_rate) {
        int n_mutations = 2;
        int split_type;
        pos new_pos = start; //continue where we left off

        switch(rand()%n_mutations) {
            case 0:
                split_type = rand()%5; //determine what reroute to perform
                //0=left, 1=right, 2=both
                if(split_type != 1) {
                    Direction ldir = left_dir(to);

                    if(distanceToEdge(ldir, start)-1 > 1 && parent_remainder > 2) {
                        int l = rand()%(distanceToEdge(ldir, start)-1)+1;
                        int turn_l = rand()%(parent_remainder-1)+1;

                        new_pos = uPath(ldir, to, l, turn_l, width, mut_rate*0.4, start);
                    }
                }
                if(split_type != 0) {
                    Direction rdir = right_dir(to);

                    if(distanceToEdge(rdir, start) > 1 && parent_remainder > 2) {
                        int l = rand()%(distanceToEdge(rdir, start)-1)+1;
                        int turn_l = rand()%(parent_remainder-1)+1;

                        new_pos = uPath(rdir, to, l, turn_l, width, mut_rate*0.4, start);
                    }
                }
                return new_pos;

            case 1:
                split_type = rand()%5; //determine what split to perform

                //split_type: 0=left, 1=right, 2=both
                if(split_type != 1) {
                    Direction ldir = left_dir(to);
                    int max_length = distanceToEdge(ldir, start)-1;

                    if(max_length > 1) {
                        int l = rand()%(max_length-1)+1;
                        start.advance(ldir, 1);
                        pos left = start; left.advance(ldir, l + 1);

                        straightPath(ldir, width, mut_rate*0.5, start, left);
                    }
                    else split_type = 1;
                }
                if(split_type != 0) {
                    Direction rdir = right_dir(to);
                    int max_length = distanceToEdge(rdir, start) - 1;

                    if(max_length > 1) {
                        int l = rand()%(max_length-1)+1;
                        start.advance(rdir, 1);
                        pos right = start; right.advance(rdir, l + 1);

                        straightPath(right_dir(to), width, mut_rate*0.5, start, right);
                    }
                }

                return new_pos;
        }
    }
    return start;
}

void LevelGenerator::straightPath(Direction d, int width, double mut_rate, pos start, pos end) {

    int i = 0;
    while(start.row < height-1 && start.col < height-1 &&
          start.row > 0      && start.col > 0) {

        board[start.row][start.col] = 'F';

        if(start.row == end.row && start.col == end.col)
            return;

        if((i != 0 && i%width == 0)) {
            int m;
            if(d == DIR_RIGHT || d == DIR_LEFT)
                m = abs(end.col - start.col);
            else
                m = abs(end.row - start.row);

            start = mutatePath(d, m, width, mut_rate, start);

        }

        start.advance(d, 1);
        i++;
    }

}

pos LevelGenerator::uPath(Direction d, Direction turn_d, int length, int turn_length, int width, double mut_rate, pos start) {
        // std::cerr << "start uPath" << std::endl;
        // std::cerr << d << " & "<< start.row << ", " << start.col << ": " << distanceToEdge(d, start) << std::endl <<
        // "l=" << length << ", l_turn=" << turn_length << std::endl << "-------------------" << std::endl;

        pos turn1 = start;
        turn1.advance(d, length);

        pos turn2 = turn1;
        turn2.advance(turn_d, turn_length);

        pos end = start;
        end.advance(turn_d, turn_length);

        // board[start.row][start.col] = '*';
        // board[turn1.row][turn1.col] = '1';
        // board[turn2.row][turn2.col] = '2';
        // board[end.row][end.col] = 'E';
        // printCharBoard();

        straightPath(d, width, mut_rate, start, turn1);
        turn1.advance(turn_d, 1); //make turn

        straightPath(turn_d, width, mut_rate, turn1, turn2);
        turn2.advance(opposite_dir(d), 1);

        straightPath(opposite_dir(d), width, mut_rate, turn2, end);

        return end;
}
