#include "curses_render.h"
#include "playerstate.h"
extern "C" {
#include <curses.h>
}
#include <iostream>
CursesRender::CursesRender() {
    WINDOW * mainwin;
    if ( (mainwin = initscr()) == NULL ) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(0);
    keypad(mainwin,true);
//    mvaddstr(13, 33, "Hello, world!");
    refresh();

}
CursesRender::~CursesRender() {
    delwin(mainwin);
    endwin();
    refresh();
    std::cout << "curses destroyed" << std::endl;
}

void CursesRender::renderBlock(short type, int x, int y) {
    char c;
    if (type == -1) {
        c = symbols[9];
    }
    else c = symbols[type];
    mvaddch(30+2-y,x+2,c);
}

void CursesRender::render(PlayerState *gs) {
    for (int x = 0; x < gs->sizex; x++) {
        for (int y = 0; y < gs->sizey; y++) {
            renderBlock(gs->field[x][y], x, y);
        }
    }
    if (!gs->blockDropped) {
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            if (gs->droppingBlock[x][y] > 0 )
            renderBlock(gs->droppingBlock[x][y], x+gs->droppingBlockX, y+gs->droppingBlockY);
        }
    }
    }
    
    refresh();
}

void CursesRender::debug(const char* msg) {
    mvaddstr(0,0,msg);
    refresh();
}

char CursesRender::getKey() {
    int ch;
    if ((ch = getch()) != ERR) {
        if (ch == KEY_LEFT) {
            debug("left");
        }
        return ch;
    }
    else {
        return false;
    }
}