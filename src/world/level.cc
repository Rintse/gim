#include "world/level.h"

Level::Level(){}

Level::Level(int width, int height) {
    board = new Square*[width];
    for(int i = 0; i < width; ++i) {
        board[i] = new Square[height];
    }
}

Level::~Level() {

}
