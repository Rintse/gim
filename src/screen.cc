#include "screen.h"
#include "game.h"
#include <iostream>

Screen::Screen(Game* g) {
    game = g;
}

Screen::~Screen() {
    delwin(win);
	endwin();
}

WINDOW* Screen::init() {
    initscr();
	noecho();
    curs_set(0);
    win = newwin(LVL_HEIGHT, 3*LVL_WIDTH, 0, 0);
	keypad(win, TRUE);
    nodelay(win, TRUE);

    return win;
}

void Screen::drawGame() {
    for(int j = 0; j < LVL_HEIGHT; j++) {
        for(int i = 0; i < LVL_WIDTH; i++) {
            Square* s = game->getLevel()->getSquare(i,j);
            char c;
            if(s->getPlayer() != 0) {
                c = s->getPlayer()->token();
            }
            else if(s->getEnemy() != 0) {
                c = 'x';
            }
            else if(s->getProjectile() != 0) {
                c = 'o';
            }
            else {
                c = s->token();
            }

            wmove(win, j, 1+(3*i));
            waddch(win, c);
        }
    }

    wrefresh(win);
}

// Menu popup
// void Sheetview::menu(int y, int x) {
// 	curs_set(0);
// 	popup = newwin(3, 17, y, x);
// 	box(popup, 0, 0);
// 	wrefresh(popup);
// 	keypad(popup, true);
// }
