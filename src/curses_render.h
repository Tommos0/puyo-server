#ifndef CURSES_RENDER_H
#define CURSES_RENDER_H

#include "playerstate.h"

extern "C" {
    #include <curses.h>
}

class CursesRender {
    private:
        WINDOW * mainwin;
        const char symbols[10] = { '.','2', '3', '4', '5', '6' ,'7' ,'8' ,'9' ,'A' };
        void renderBlock(short, int,int);
    public:
        CursesRender();
        ~CursesRender();
        void render(PlayerState *);
        void debug(const char *);
        char getKey();
        static const int K_LEFT = KEY_LEFT;
        static const int K_RIGHT = KEY_RIGHT;
        static const int K_UP = KEY_UP;
        static const int K_DOWN = KEY_DOWN;
};

#endif //CURSES_RENDER_H