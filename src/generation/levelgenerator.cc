#include "generation/levelgenerator.h"
#include "world/squares/wall.h"
#include "world/squares/empty.h"
#include "world/squares/door.h"
#include "tools/distance.h"
#include "tools/fastrandom.h"

#include <stdlib.h>

// 'I' IN
// 'O' OUT
//  0  EMPTY

LevelGenerator::LevelGenerator(int w, int h) {
    initBoard(w, h, DIR_LEFT, h/2, DIR_RIGHT, h/2);
    mut = 0.7;
    srand(20);
    // srand(time(NULL));
}

//d: side of the board, the door is on
pos LevelGenerator::generateDoors(Direction d, int i) const {
    switch(d) {
        case DIR_UP:
            return {i, 0};
        case DIR_DOWN:
            return {i, height-1};
        case DIR_LEFT:
            return {0, i};
        case DIR_RIGHT:
            return {width-1, i};
    }
    return {0,0};
}

void LevelGenerator::setLevel(Level* l) {
    level = l;
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
        for(int i = 0; i < width; i++) {
            if(board[i] != NULL)
                delete[] board[i];
        }
        delete[] board;
    }
    std::cerr << "LevelGenerator: Allocate board" << std::endl;
    board = new char*[width];

    for(int i = 0; i < width; i++)
        board[i] = new char[height];

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++)
            if(i == entrance.x && j == entrance.y)
                board[i][j] = 'I';
            else if(i == exit.x && j == exit.y)
                board[i][j] = 'O';
            else //if(i > 0)
                board[i][j] = '-';
            // else
            //     board[i][j] = '1';
        }
}

void LevelGenerator::initBoard(Level*l, int w, int h,
                               Direction in_dir, int in_index,
                               Direction out_dir, int out_index) {
   level = l;

   initBoard(w, h, in_dir, in_index, out_dir, out_index);
}

void LevelGenerator::printCharBoard() const {
    std::cerr << "LevelGenerator: Print board" << std::endl;
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "=======================================================" << std::endl;
}

void LevelGenerator::clearChar() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            if(i == entrance.x && j == entrance.y)
                board[i][j] = 'I';
            else if(i == exit.x && j == exit.y)
                board[i][j] = 'O';
            else
                board[i][j] = '-';
        }
    }
}

Square* LevelGenerator::createSquare(char c, int x, int y) {
    switch(c) {
        case '-': return new WallSquare(x, y);
        case 'F': return new EmptySquare(x, y);
        case 'I': return new DoorSquare(x, y, in);
        case 'O': return new DoorSquare(x, y, out);

        default:
            return new WallSquare(x, y);
    }
}

Square*** LevelGenerator::createBoard() {
    std::cerr << "LevelGenerator: createBoard start" << std::endl;
    Square*** square_board = new Square**[width];
    for(int i = 0; i < width; i++)
        square_board[i] = new Square*[height];

    for(int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
            square_board[i][j] = createSquare(board[i][j], i, j);

    // printCharBoard();
    clearChar();
    return square_board;
}

// Square*** LevelGenerator::createBoard() {
//     std::cerr << "LevelGenerator: createBoard start" << std::endl;
//     Square*** square_board = new Square**[width];
//     for(int i = 0; i < width; i++)
//         square_board[i] = new Square*[height];
//
//     for(int i = 0; i < width; i++)
//         for(int j = 0; j < height; j++)
//             square_board[i][j] = createSquare(board[j][i], j, i);
//
//     clearChar();
//     return square_board;
// }

Square*** LevelGenerator::bossRoom(int w, int h, pos door) {
    Square*** square_board = new Square**[w];
    for(int i = 0; i < w; i++)
        square_board[i] = new Square*[h];

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            // Edges
            if(i == 0 || j == 0 || i == w-1 || j == h-1) {
                // Door on bottom
                if(j == h-1 && i == door.x) {
                    square_board[i][j] = new DoorSquare(i,j,DIR_DOWN);
                }
                else { // Walls around the entire thing
                    square_board[i][j] = new WallSquare(i,j);
                }
            }
            else {
                square_board[i][j] = new EmptySquare(i,j);
            }
        }
    }

    return square_board;
}

Square*** LevelGenerator::startRoom(int w, int h, int room_doory, int boss_doorx) {
    std::cerr << "LevelGenerator: startRoom start" << std::endl;

    Square*** square_board = new Square**[w];
    for(int i = 0; i < w; i++)
        square_board[i] = new Square*[h];

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            // Edges
            if(i == 0 || j == 0 || i == w-1 || j == h-1) {
                // Doors on top, left, right
                if( (j == 0 && i == boss_doorx) ||
                ((i == 0 || i == w-1) && j == room_doory)) {
                    Direction dir;
                    if(i == 0) dir = DIR_LEFT;
                    else if(i == w-1) dir = DIR_RIGHT;
                    else dir = DIR_UP;
                    square_board[i][j] = new DoorSquare(i,j,dir);
                }
                else { // Walls around the entire thing
                    square_board[i][j] = new WallSquare(i,j);
                }
            }
            // Hallway
            else if((i < boss_doorx-6 && j < room_doory-6) || (i > boss_doorx+6 && j < room_doory-6) ||
                    (i < boss_doorx-6 && j > room_doory+6) || (i > boss_doorx+6 && j > room_doory+6)) {
                square_board[i][j] = new WallSquare(i,j);
            }
            else {
                square_board[i][j] = new EmptySquare(i,j);
            }
        }
    }

    return square_board;
}

Square*** LevelGenerator::randomRoom(int w, int h, int room_doory, FastRandom &r) {
    std::cerr << "LevelGenerator: startRoom start" << std::endl;

    Square*** square_board = new Square**[w];
    for(int i = 0; i < w; i++)
        square_board[i] = new Square*[h];

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            if(i == 0 || j == 0 || i == w-1 || j == h-1) {
                if((i == 0 || i == w-1) && j == room_doory) {
                    Direction dir = i==0 ? DIR_LEFT : DIR_RIGHT;
                    square_board[i][j] = new DoorSquare(i,j,dir);
                }
                else {
                    square_board[i][j] = new WallSquare(i,j);
                }
            }
            else {
                if(r.getLong() % 10 == 0 && dist(i,j, w-1,room_doory) > 3) {
                    square_board[i][j] = new WallSquare(i,j);
                }
                else {
                    square_board[i][j] = new EmptySquare(i,j);
                    // Only spawn enemy if far enough from doors
                    if(dist(i,j, 0,room_doory) > 15 && dist(i,j, w-1,room_doory) > 15) {
                        double rand = r.getDouble();
                        if(rand < 0.01) { // Certain chance to spawn enemy
                            spawnEnemy(square_board[i][j]); //TODO: magic num
                            std::cout << "Enemy at " << i << ", " << j << std::endl;
                        }
                        rand = r.getDouble();
                        if(rand < 0.005) {
                            spawnHeart(square_board[i][j]);
                            std::cout << "Heart at " << i << ", " << j << std::endl;
                        }
                    }
                }
            }
        }
    }

    return square_board;
}

Square*** LevelGenerator::cpeRoom(Direction in_dir, int in_offset, Direction out_dir, int out_offset) {
    entrance = generateDoors(in_dir, in_offset);
    exit = generateDoors(out_dir, out_offset);

    in = in_dir;
    out = out_dir;

    return cpeRoom();
}

Square*** LevelGenerator::cpeRoom() {
    std::cerr << "LevelGenerator: cpeRoom start" << std::endl;

    int width = 1; //0 = 1 path, 1 = 3 path, 2 = 5 path

    pos walk = entrance;
    walk.advance(opposite_dir(in), 1);

    pos finish = exit;
    finish.advance(opposite_dir(out), 1);

    straightPath(opposite_dir(in), width, mut, walk, finish);

    //TODO? arbitrary starting position RL/UD: Z/N-shape random corners

    return createBoard();
}

//No.  squares between p and edge d
int LevelGenerator::distanceToEdge(Direction d, pos p) {
    switch(d) {
        case DIR_UP:    return p.y;
        case DIR_DOWN:  return height-1-p.y;
        case DIR_LEFT:  return p.x;
        case DIR_RIGHT: return width-1-p.x;
    }
    return -1;
}

pos LevelGenerator::mutatePath(Direction to, int parent_remainder, int interval, double mut_rate, pos start) {
    double r = rand(); double max = RAND_MAX; double c = r/max;

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

                    if(distanceToEdge(ldir, start)-1 > 1 && parent_remainder-interval > 2) {
                        int l = rand()%(distanceToEdge(ldir, start)-1)+1;
                        int turn_l = rand()%(parent_remainder-1-interval)+1;

                        new_pos = uPath(ldir, to, l, turn_l, interval, mut_rate*0.4, start);
                    }
                }
                if(split_type != 0) {
                    Direction rdir = right_dir(to);

                    if(distanceToEdge(rdir, start) > 1 && parent_remainder-interval > 2) {
                        int l = rand()%(distanceToEdge(rdir, start)-1)+1;
                        int turn_l = rand()%(parent_remainder-1-interval)+1;

                        new_pos = uPath(rdir, to, l, turn_l, interval, mut_rate*0.4, start);
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

                        straightPath(ldir, interval, mut_rate*0.5, start, left);
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

                        straightPath(right_dir(to), interval, mut_rate*0.5, start, right);
                    }
                }

                return new_pos;
        }
    }
    return start;
}

void LevelGenerator::straightPath(Direction d, int interval, double mut_rate, pos start, pos end) {
    int i = 0;
    while(start.x < width-1 && start.y < height-1 &&
          start.x > 0      && start.y > 0) {

        if(board[start.x][start.y] == '-')
            board[start.x][start.y] = 'F';

        for(int k = 1; k <= interval; k++) { //path width
            if(d == DIR_RIGHT || d == DIR_LEFT) {
                if(board[start.x][start.y+k] == '-')
                    board[start.x][start.y+k] = 'F';
                if(board[start.x][start.y-k] == '-')
                    board[start.x][start.y-k] = 'F';
            }
            else {
                if(board[start.x+k][start.y] == '-')
                    board[start.x+k][start.y] = 'F';
                if(board[start.x-k][start.y] == '-')
                    board[start.x-k][start.y] = 'F';
            }
        }

        if(start.x == end.x && start.y == end.y)
            return;

        if((i > interval+1 && i%(2*(interval+1)) == 0)) {
            int m;
            if(d == DIR_RIGHT || d == DIR_LEFT)
                m = abs(end.x - start.x);
            else
                m = abs(end.y - start.y);

            if(m > interval)
                start = mutatePath(d, m, interval, mut_rate, start);

        }

        start.advance(d, 1);
        i++;
    }

}

pos LevelGenerator::uPath(Direction d, Direction turn_d, int length, int turn_length, int interval, double mut_rate, pos start) {

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

        straightPath(d, interval, mut_rate, start, turn1);
        turn1.advance(turn_d, 1); //make turn

        straightPath(turn_d, interval, mut_rate, turn1, turn2);
        turn2.advance(opposite_dir(d), 1);

        straightPath(opposite_dir(d), interval, mut_rate, turn2, end);

        return end;
}

void LevelGenerator::spawnEnemy(Square* s) {
    EmptySquare* es = dynamic_cast<EmptySquare*>(s);
    Enemy* tmp = new Enemy(level, es);
    es->setEnemy(tmp);
    enemies.insert(tmp); //TODO give enemies to level & set level pointer
}

void LevelGenerator::spawnHeart(Square* s) {
    EmptySquare* es = dynamic_cast<EmptySquare*>(s);
    es->setHeart(true);
}
