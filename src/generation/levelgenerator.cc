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
// #include "/home/majeux/cpp-tools/dbg-macro/dbg.h" //debug shit van Max

#define MIN_MUT_LENGTH 5
#define CRITICAL_MUT 0.9
#define PATH_WIDTH 1        //0 = 1 path, 1 = 3 path, 2 = 5 path

/*
    (DE)CONSTRUCTION / INITIALIZATION
*/
LevelGenerator::LevelGenerator(int w, int h, FastRandom* fr) {
    initBoard(w, h, DIR_LEFT, h/2, DIR_RIGHT, h/2);

    rand = fr;
}

LevelGenerator::~LevelGenerator() {
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
        return;
    }
    width = w; height = h;

    entrance = generateDoors(in_dir, in_index);
    exit = generateDoors(out_dir, out_index);

    in = in_dir;
    out = out_dir;

    deleteCharBoard();

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

        if(rand->getLong()%2) spawnHeart(b[temp.x][temp.y]);
        else spawnFBullet(b[temp.x][temp.y]);
    }

    for (int i = 0; i < target_powers - (int64_t)power_positions.size() && i < (int64_t)enemy_positions.size(); i++) {
        pos temp = enemy_positions[i];

        if(rand->getLong()%2) spawnHeart(b[temp.x][temp.y]);
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

Square*** LevelGenerator::cpeRoom(int d) {
    depth = d;
    power_positions.clear();
    enemy_positions.clear();
    n_floor = 0;
    n_mut = 0;

    pos walk = entrance;
    walk.advance(opposite_dir(in), 1);

    pos finish = exit;
    finish.advance(opposite_dir(out), 1);

    remain = (width - 2)/(2*PATH_WIDTH+1); //projected number of floor tiles to be  placed

    setDifficulty();

    straightPath(opposite_dir(in), walk, width-2, false);


    return createBoard();
}

Square*** LevelGenerator::testRoom(int d) {
    depth = d;

    power_positions.clear();
    enemy_positions.clear();
    n_floor = 0;
    n_mut = 0;

    pos walk = entrance;
    walk.advance(opposite_dir(in), 1);

    pos finish = exit;
    finish.advance(opposite_dir(out), 1);

    remain = (width - 2)/(2*PATH_WIDTH+1); //projected number of floor tiles to be  placed

    target_mut = 3;
    enemy_permille = 0;;
    target_powers = 0;

    straightPath(opposite_dir(in), walk, width -2, false);

    return createBoard();
}
/////////////
/*
    PATH GENERATORION
*/
int LevelGenerator::mutatePath(Direction to, int parent_remainder, double mut_rate, pos start) {
    if(rand->getDouble() < mut_rate) {
        //Determine Left/Right direction and parameter bounds
        Direction ldir = left_dir(to);
        int ldist = distanceToEdge(ldir, start);

        Direction rdir = right_dir(to);
        int rdist = distanceToEdge(rdir, start);

        //variables for left, right, left/right selection
        bool doleft = false; bool doright = false; //are L/R selected to be performed
        bool leftu = false;  bool rightu = false;  //has L/R performed a upath?

        //choose randomly between { left, right, both } if possible
        //ptherwise take available
        if(ldist > MIN_MUT_LENGTH && rdist > MIN_MUT_LENGTH) { //TODO clean up this logic?
            switch(rand->getLong()%5) {
                case 0:
                    doleft = true;
                    break;
                case 1:
                    doright = true;
                    break;
                default:
                    doleft = true;
                    doright = true;
            }
        }
        else if(ldist > MIN_MUT_LENGTH) { //only option
            doleft = true;
        }
        else if(rdist > MIN_MUT_LENGTH) { //only option
            doright = true;
        }

        int u_widthL, u_widthR;
        int min_width = 2*(PATH_WIDTH + 1); // minimum distance for worthwile uPath (ensures 1 sep between dir and back)
        //Perform mutations
        if(doleft && MIN_MUT_LENGTH < ldist - 1) {
            int l = rand->getLong()%(ldist-1-MIN_MUT_LENGTH) + MIN_MUT_LENGTH; //rand [MIN_MUT_LENGTH .. ldist-1]

            if(parent_remainder - PATH_WIDTH > min_width && rand->getLong()%10 < 6) {
                u_widthL = rand->getLong()%(parent_remainder - PATH_WIDTH - min_width) + min_width; //rand [min_width .. parent_remainder]

                uPath(ldir, to, l, u_widthL, start);
                leftu = true;
            } else
                straightPath(ldir, start, l, true);//select if uPath not possible or on 50% chance
        }
        if(doright && MIN_MUT_LENGTH < rdist-1) {
            int l = rand->getLong()%(rdist-1-MIN_MUT_LENGTH) + MIN_MUT_LENGTH; //rand [MIN_MUT_LENGTH .. rdist-1]

            if(parent_remainder - PATH_WIDTH > min_width && rand->getLong()%10 < 6) { //favor upath
                u_widthR = rand->getLong()%(parent_remainder - PATH_WIDTH - min_width) + min_width; //rand [min_width .. parent_remainder]

                uPath(rdir, to, l, u_widthR, start);
                rightu = true;
            } else
                straightPath(rdir, start, l, true); //select if uPath not possible or on 50% chance
        }

        //determine behaviour of continuing path
        if(leftu && rightu) {
            int r = rand->getLong()%9;
            //path has been rerouted at least once. Continuing is optional
            if(r < 4)
                return u_widthL;
            if(r < 8)
                return u_widthR;

            return 1;
        }
        if(leftu) { //TODO tweak
            return rand->getLong()%4 == 0 ? 1 : u_widthL;
        }
        if(rightu) {
            return rand->getLong()%4 == 0 ? 1 : u_widthR;
        }
        //path has only produced dead ends. Critical path must continue from start

    }
    return 1;
}

void LevelGenerator::straightPath(Direction d, pos start, int length, bool power) {
    int i = 0;

    if(power) { //beetje hacky, alleen puur straightPath heeft power aan het einde
        n_mut++;
        remain += length/(2*PATH_WIDTH+1);
    }

    while(start.x < width-1 && start.y < height-1 && start.x > 0 && start.y > 0
            && i < length) {

        if(power && i == length - 1 && board[start.x][start.y] == '-')
            power_positions.push_back(start);

        placeFloor(start.x, start.y, true);

        for(int k = 1; k <= PATH_WIDTH; k++) { //path width
            if(d == DIR_RIGHT || d == DIR_LEFT) {
                placeFloor(start.x, start.y+k);
                placeFloor(start.x, start.y-k);
            }
            else {
                placeFloor(start.x+k, start.y);
                placeFloor(start.x-k, start.y);
            }
        }

        pos temp = start; temp.advance(d, 2 + PATH_WIDTH, width, height);

        if(power && temp.x != start.x && temp.y != start.y && board[temp.x][temp.y] == 'C') { //there will be an intersection
            if(i > length/2)
                power_positions.push_back(start);
            // printCharBoard();
            return;
        }
        int step = 1;
        if((i > PATH_WIDTH && length - i > PATH_WIDTH
                && i%(2*PATH_WIDTH+1) == 0)) {
            double mut_rate = (double)(target_mut-n_mut)/remain;
            step = mutatePath(d, length - i, mut_rate, start);
        }

        start.advance(d, step);
        i += step;
    }

}

void LevelGenerator::uPath(Direction d, Direction turn_d, int length, int turn_length, pos start) {
    n_mut++;
    remain += (2*length + turn_length)/(2*PATH_WIDTH+1);

    pos turn1 = start;
    turn1.advance(d, length);

    pos turn2 = turn1;
    turn2.advance(turn_d, turn_length);

    // board[start.x][start.y] = '*';
    // board[turn1.x][turn1.y] = '1';
    // board[turn2.x][turn2.y] = '2';
    // printCharBoard();

    straightPath(d, start, length+1, false);

    straightPath(turn_d, turn1, turn_length+1, false);

    straightPath(opposite_dir(d), turn2, length+1, false);
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
            break;
        case 6:
            target_mut = 35;
            break;
        default:
            target_mut = 35;

    }
    //Tiers: {0-3}, {3-9}, {10-18}, {19-28} ...
    int sign = rand->getLong()%2 ? 1 : -1;
    enemy_permille = 5 + (depth-1) + sign*(rand->getLong()%3);
    target_powers = depth;
}
