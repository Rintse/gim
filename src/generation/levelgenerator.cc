#include "generation/levelgenerator.h"

#include "world/squares/wall.h"
#include "world/squares/empty.h"
#include "world/squares/door.h"

#include "tools/distance.h"
#include "tools/fastrandom.h"

#include "entities/powerups/hp.h"
#include "entities/powerups/fasterbullets.h"

#include <stdlib.h>
#include <algorithm>

#define MIN_MUT_LENGTH 3
#define CRITICAL_MUT 0.9

/*
    (DE)CONSTRUCTION / INITIALIZATION
*/
LevelGenerator::LevelGenerator(int w, int h) {
    initBoard(w, h, DIR_LEFT, h/2, DIR_RIGHT, h/2);

    // rand = new FastRandom(time(NULL));
}

LevelGenerator::~LevelGenerator() {
    // delete rand;

    deleteCharBoard();
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

    deleteCharBoard();

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
/////////////

/*
    SETTERS
*/
void LevelGenerator::setLevel(Level* l) {
    level = l;
}
/////////////
/*
    SQUARE PLACEMENT
*/
void LevelGenerator::spawnEnemy(Square* s) {
    EmptySquare* es = dynamic_cast<EmptySquare*>(s);
    Enemy* tmp = new Enemy(level, es);
    es->setEnemy(tmp);
}

void LevelGenerator::spawnHeart(Square* s) {
    EmptySquare* es = dynamic_cast<EmptySquare*>(s);
    es->setPowerup(new Hp);
}

void LevelGenerator::spawnFBullet(Square* s) {
    EmptySquare* es = dynamic_cast<EmptySquare*>(s);
    es->setPowerup(new FasterBullets);
}

void LevelGenerator::placePowers(Square *** b) {
    std::random_shuffle(power_positions.begin(), power_positions.end());

    // printCharBoard();

    for (int i = 0; i < target_powers && i < (int64_t)power_positions.size(); i++) {
        pos temp = power_positions[i];
        // dbg(temp.x); dbg(temp.y);
        if(rand()%2) spawnHeart(b[temp.x][temp.y]);
        else spawnFBullet(b[temp.x][temp.y]);
    }

    for (int i = 0; i < target_powers - (int64_t)power_positions.size() && i < (int64_t)enemy_positions.size(); i++) {
        pos temp = enemy_positions[i];
        // dbg(temp.x); dbg(temp.y);
        if(rand()%2) spawnHeart(b[temp.x][temp.y]);
        else spawnFBullet(b[temp.x][temp.y]);
    }
}

void LevelGenerator::placeEnemies(Square *** b) {
    std::random_shuffle(enemy_positions.begin(), enemy_positions.end());

    for (int i = 0; i < std::max(1, (enemy_permille*n_floor)/1000) && i < (int64_t)enemy_positions.size(); i++) {
        pos temp = enemy_positions.back();
        spawnEnemy(b[temp.x][temp.y]);

        enemy_positions.pop_back();
    }
}

void LevelGenerator::placeFloor(int x, int y, bool critical) {
    if(x >= width-1 || y >= height-1 || x <= 0 || y <= 0)
        return;

    if(board[x][y] == '-') {
        if(dist(x, y, entrance.x, entrance.y) > 15 && dist(x, y, exit.x, exit.y) > 15)
        enemy_positions.push_back({x, y});

        n_floor++;
    }

    if(critical)
        board[x][y] = 'C';
    else
        board[x][y] = 'F';
}
/////////////
/*
    CHAR -> SQUARE BOARD CONVERSION
*/
Square* LevelGenerator::createSquare(char c, int x, int y) {

    switch(c) {
        case '-':
            return new WallSquare(x, y);
        case 'F': case 'C':
            return new EmptySquare(x, y);
        case 'I':
            return new DoorSquare(x, y, in);
        case 'O':
            return new DoorSquare(x, y, out);

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

    placeEnemies(square_board);
    placePowers(square_board);
    // printCharBoard();
    clearChar();
    return square_board;
}
/////////////
/*
    AUX BOARD FUNCTIONS
*/
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

void LevelGenerator::deleteCharBoard() {
    if(board != NULL) { //TODO mogelijk resizen
        std::cerr << "LevelGenerator: Delete board" << std::endl;
        for(int i = 0; i < width; i++) {
            if(board[i] != NULL)
                delete[] board[i];
        }
        delete[] board;
    }
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
/////////////
/*
    ROOM GENERATORS
*/
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

Square*** LevelGenerator::bossRoom(int w, int h, pos door) {
    Square*** square_board = new Square**[w];
    for(int i = 0; i < w; i++)
    square_board[i] = new Square*[h];

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            // Edges
            if(j == door.y && i == door.x)
            square_board[i][j] = new DoorSquare(i,j,DIR_DOWN);
            else if(i == 0 || j == 0 || i == w-1 || j == h-1)
            square_board[i][j] = new WallSquare(i,j);
            else if(j < 7)
            square_board[i][j] = new EmptySquare(i,j,true);
            else
            square_board[i][j] = new EmptySquare(i,j);
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

Square*** LevelGenerator::cpeRoom(Direction in_dir, int in_offset, Direction out_dir, int out_offset, int d) {
    entrance = generateDoors(in_dir, in_offset);
    exit = generateDoors(out_dir, out_offset);

    in = in_dir;
    out = out_dir;
    depth = d;

    return cpeRoom();
}

Square*** LevelGenerator::cpeRoom() {
    std::cerr << "LevelGenerator: cpeRoom start" << std::endl;

    int p_width = 1; //0 = 1 path, 1 = 3 path, 2 = 5 path

    power_positions.clear();
    enemy_positions.clear();
    n_floor = 0;
    n_mut = 0;

    pos walk = entrance;
    walk.advance(opposite_dir(in), 1);

    pos finish = exit;
    finish.advance(opposite_dir(out), 1);

    remain = (width - 2)/(2*p_width+1); //projected number of floor tiles to be  placed

    setDifficulty();

    straightPath(opposite_dir(in), p_width, walk, finish, width -2, false);

    // dbg(n_mut);
    return createBoard();
}
/////////////
/*
    PATH GENERATORION
*/
pos LevelGenerator::mutatePath(Direction to, int parent_remainder, int path_offset, double mut_rate, pos start) {
    double r = rand(); double max = RAND_MAX; double c = r/max;

    if(c < mut_rate) {
        pos lpos, rpos;

        //Determine Left/Right direction and parameter bounds
        Direction ldir = left_dir(to);
        int ldist = distanceToEdge(ldir, start);

        Direction rdir = right_dir(to);
        int rdist = distanceToEdge(rdir, start);

        //variables for left, right, left/right selection
        bool doleft = false; bool doright = false; //are L/R selected to be performed
        bool leftu = false;  bool rightu = false;  //has L/R performed a upath?

        int min_length = 2*path_offset + 1;

        //choose randomly between { left, right, both } if possible
        //ptherwise take available
        if(ldist > min_length && rdist > min_length) { //TODO clean up this logic?
            switch(rand()%5) {
                case 0:
                doleft = true;
                break;
                case 1:
                doright = true;
                break;
                case 3: case 4: case 5:
                doleft = true;
                doright = true;
            }
        }
        else if(ldist > min_length) { //only option
            doleft = true;
        }
        else if(rdist > min_length) { //only option
            doright = true;
        }

        int u_widthL, u_widthR;
        int min_width = 2*(path_offset + 1); // minimum distance for worthwile uPath (ensures 1 sep between dir and back)
        //Perform mutations
        if(doleft && MIN_MUT_LENGTH < ldist - 1) {
            int l = rand()%(ldist-1-MIN_MUT_LENGTH) + MIN_MUT_LENGTH;
            pos end = start; end.advance(ldir, l);

            if(parent_remainder > min_width && rand()%10 < 5) {
                u_widthL = rand()%(parent_remainder - min_width) + min_width;

                lpos = uPath(ldir, to, l, u_widthL, path_offset, start);
                leftu = true;
            } else
            straightPath(ldir, path_offset, start, end, l, true);//select if uPath not possible or on 50% chance
        }
        if(doright && MIN_MUT_LENGTH < rdist-1) {
            int l = rand()%(rdist-1-MIN_MUT_LENGTH) + MIN_MUT_LENGTH;
            pos end = start; end.advance(rdir, l);

            if(parent_remainder > min_width && rand()%10 < 5) { //favor upath
                u_widthR = rand()%(parent_remainder - min_width) + min_width;

                rpos = uPath(rdir, to, l, u_widthR, path_offset, start);
                rightu = true;
            } else
            straightPath(rdir, path_offset, start, end, l, true); //select if uPath not possible or on 50% chance
        }

        //determine behaviour of continuing path
        pos new_pos = start;
        if(leftu && rightu) {
            //path has been rerouted at least once. Continuing is optional
            if(u_widthL > u_widthR) {
                straightPath(to, path_offset, rpos, lpos, u_widthL-u_widthR, false);
                new_pos = lpos;
            }
            else if(u_widthL < u_widthR) {
                straightPath(to, path_offset, lpos, rpos, u_widthR-u_widthL, false);
                new_pos = rpos;
            }

            return new_pos;
        }
        if(leftu)
            return lpos;
        if(rightu)
            return rpos;
        //path has only produced dead ends. Critical path must continue from start

    }
    return start;
}

void LevelGenerator::straightPath(Direction d, int path_offset, pos start, pos end, int length, bool power) {
    int i = 0;

    if(power) { //beetje hacky, alleen puur straightPath heeft power aan het einde
        n_mut++;
        remain += length/(2*path_offset+1);
    }

    while(start.x < width-1 && start.y < height-1 && start.x > 0 && start.y > 0) {

        if(power && i == length && board[start.x][start.y] == '-')
            power_positions.push_back(start);

        placeFloor(start.x, start.y, true);

        for(int k = 1; k <= path_offset; k++) { //path width
            if(d == DIR_RIGHT || d == DIR_LEFT) {
                placeFloor(start.x, start.y+k);
                placeFloor(start.x, start.y-k);
            }
            else {
                placeFloor(start.x+k, start.y);
                placeFloor(start.x-k, start.y);
            }
        }

        if(start.x == end.x && start.y == end.y)
            return;

        pos temp = start; temp.advance(d, 2 + path_offset, width, height);

        if(power && temp.x != start.x && temp.y != start.y && board[temp.x][temp.y] == 'C') { //there will be an intersection
            if(i > length/2)
                power_positions.push_back(start);
            std::cerr << "path truncated" << std::endl;
            // printCharBoard();
            return;
        }

        if((i > path_offset+1 && i%(2*path_offset+1) == 0)) {
            remain--;
            int r;
            if(d == DIR_RIGHT || d == DIR_LEFT)
            r = abs(end.x - start.x);
            else
            r = abs(end.y - start.y);

            if(r > path_offset) { //for old mutation: change (double)... to mut_rate
                double mut_rate = (double)(target_mut-n_mut)/remain;
                start = mutatePath(d, r, path_offset, mut_rate, start);
            }
        }

        start.advance(d, 1);
        i++;
    }

}

pos LevelGenerator::uPath(Direction d, Direction turn_d, int length, int turn_length, int path_offset, pos start) {
    n_mut++;
    remain += (2*length + turn_length)/(2*path_offset+1);

    pos turn1 = start;
    turn1.advance(d, length);

    pos turn2 = turn1;
    turn2.advance(turn_d, turn_length);

    pos end = start;
    end.advance(turn_d, turn_length);

    // board[start.x][start.y] = '*';
    // board[turn1.x][turn1.y] = '1';
    // board[turn2.x][turn2.y] = '2';
    // board[end.x][end.y] = 'E';
    // printCharBoard();

    straightPath(d, path_offset, start, turn1, length, false);

    straightPath(turn_d, path_offset, turn1, turn2, turn_length, false);

    straightPath(opposite_dir(d), path_offset, turn2, end, length, false);

    return end;
}
/////////////
/*
    PROCEDURAL DIFFICULTY
*/
void LevelGenerator::setDifficulty() {
    switch(depth) { //TODO determine proper scaling
        case 1:
            target_mut = 3;
            break;
        case 2:
            target_mut = 7;
            break;
        case 3:
            target_mut = 12;
            break;
        case 4:
            target_mut = 18;
            break;
        case 5:
            target_mut = 25; //seems to be the maximum for a level that is not empty
                             //possible TODO: dissallow new paths to intersect
            break;
        case 6:
            target_mut = 35;
            break;
        default:
            target_mut = 25;

    }
    //Tiers: {0-3}, {3-9}, {10-18}, {19-28} ...
    int sign = rand()%2 ? 1 : -1;
    enemy_permille = 5 + (depth-1) + sign*(rand()%3);
    target_powers = depth;
}
