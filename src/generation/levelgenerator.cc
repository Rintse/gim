#include "generation/levelgenerator.h"
#include <stdlib.h>


// 'I' IN
// 'O' OUT
//  0  EMPTY

//d: side of the board, the door is on
pos LevelGenerator::generateDoors(DIR_MASK d, int i) const {
    switch(d) {
        case UP:
            return {0, i};
        case DOWN:
            return {height-1,i};
        case LEFT:
            return {i, 0};
        case RIGHT:
            return {i, width-1};
        default:
            return {0,0};
    }
}

void LevelGenerator::initBoard(int w, int h,
                               DIR_MASK in_dir, int in_index,
                               DIR_MASK out_dir, int out_index)
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
    srand(9);
    srand(time(NULL));
}

LevelGenerator::LevelGenerator(int w, int h) {
    initBoard(w, h, LEFT, h/2, RIGHT, h/2);
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
    //TODO
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
    walk.advance(reverse(in), 1);
    // if(in == reverse(out) && (entrance.row == exit.row || entrance.col == exit.col)) {
    //     if(in == RIGHT || in ==LEFT) {
            straightUntil(reverse(in), 2, 0.7, walk, exit);
    //     }
    //     if(in == UP || in == DOWN) {
    //         straightPath(reverse(in), abs(exit.row - entrance.row), 1, mut, walk);
    //     }
    // }
    //TODO arbitrary starting position RL/UD: Z/N-shape random corners

    return NULL;
}

//No.  squares between p and edge d
int LevelGenerator::distanceToEdge(DIR_MASK d, pos p) {
    switch(d) {
        case UP:    return p.row;
        case DOWN:  return height-1-p.row;
        case LEFT:  return p.col;
        case RIGHT: return width-1-p.col;
        default:
            return -1;
    }
}

pos LevelGenerator::mutatePath(DIR_MASK to, int m, int width, double mut_rate, pos start) {
    double r = rand();
    double max = RAND_MAX;
    // double c = (double)rand.getLong()/(double)rand.getMax();
    double c = r/max;
    // std::cerr << "r_num : " << r << std::endl << std::endl;
    // std::cerr << "r_max : " << max << std::endl << std::endl;
    // std::cerr << "chance: " << c << std::endl << std::endl;
    if( c < mut_rate) {
        int n_mutations = 2;
        int split_type;
        pos new_pos = start;

        switch(rand()%n_mutations) {
            case 0:
                split_type = rand()%5; //determine what reroute to perform
                //0=left, 1=right, 2=both
                if(split_type != 1) {
                    DIR_MASK ldir = turnLeft(to);

                    if(distanceToEdge(ldir, start) > 1 && m > 2) {
                        int l = rand()%(distanceToEdge(ldir, start)-1)+1;
                        int turn_l = rand()%(m-1)+1;;

                        new_pos = uPath(ldir, to, l, turn_l, width, mut_rate*0.6, start);
                    }
                }
                if(split_type != 0) {
                    DIR_MASK rdir = turnRight(to);

                    if(distanceToEdge(rdir, start) > 1 && m > 2) {
                        int l = rand()%(distanceToEdge(rdir, start)-1)+1;;
                        // std::cerr << "d=" << distanceToEdge(rdir, start) << std::endl;
                        int turn_l = rand()%(m-1)+1;;

                        new_pos = uPath(rdir, to, l, turn_l, width, mut_rate*0.6, start);
                    }
                }
                return new_pos; //TODO: properly discontinue original path (on some P?)

            case 1: //split {Left T, Right T, + split}
                split_type = rand()%5; //determine what split to perform

                //split_type: 0=left, 1=right, 2=both
                if(split_type != 1) {
                    pos left = start; left.advance(turnLeft(to), 1);
                    straightPath(turnLeft(to), rand()%distanceToEdge(turnLeft(to), start),    width, mut_rate*0.7, left);
                }
                if(split_type != 0) {
                    pos right = start; right.advance(turnRight(to), 1);
                    straightPath(turnRight(to), rand()%distanceToEdge(turnRight(to), start), width, mut_rate*0.7, right);
                }

                return new_pos;
        }
    }
    return start;
}

void LevelGenerator::straightPath(DIR_MASK d, int length, int width, double mut_rate, pos start) {

    // std::cerr << "LevelGenerator: straightPath(dir=" << d << ", length=" << length << ", width=" << width << ", mut=" << mut_rate << ", start=(" << start.row << ", " << start.col << ") )" << std::endl;

    for(int i = 0; i < length; start.advance(d, 1), i++) {
        if(start.col >= width && start.row >= height) //edge of screen
            return;
        if(board[start.row][start.col] == 'O') //rejoined the path
            return;

        if(board[start.row][start.col] == 'F') //rejoined the path
            return;

        board[start.row][start.col] = 'F'; //floor

        if((i != 0 && i%width == 0))
            start = mutatePath(d, length-i, width, mut_rate, start);
    }
}

void LevelGenerator::straightUntil(DIR_MASK d, int width, double mut_rate, pos start, pos end) {

    int i = 0;
    while(start.row < height && start.col < height &&
          start.row >= 0      && start.col >= 0) {
        // std::cerr << start.row << ", " << start.col << " | vs | " << end.row << ", " << end.col << std::endl;

        board[start.row][start.col] = 'F';

        if(start.row == end.row && start.col == end.col)
            return;

        if((i != 0 && i%width == 0)) {
            int m;
            if(d == RIGHT || d == LEFT)
                m = abs(end.col - start.col);
            else
                m = abs(end.row - start.row);

            start = mutatePath(d, m, width, mut_rate, start);

        }

        start.advance(d, 1);
        i++;
    }

}

pos LevelGenerator::uPath(DIR_MASK d, DIR_MASK turn_d, int length, int turn_length, int width, double mut_rate, pos start) {
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

        straightUntil(d, width, mut_rate, start, turn1);
        turn1.advance(turn_d, 1); //make turn

        straightUntil(turn_d, width, mut_rate, turn1, turn2);
        turn2.advance(reverse(d), 1);

        straightUntil(reverse(d), width, mut_rate, turn2, end);

        return end;
}
