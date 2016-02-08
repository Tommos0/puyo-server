#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "network.h"
#include "game.h"

#ifdef CURSES
extern "C" {
    #include <curses.h>
}
void curses_print() {

 WINDOW * mainwin;
 if ( (mainwin = initscr()) == NULL ) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }

    /*  Display "Hello, world!" in the centre of the
        screen, call refresh() to show our changes, and
        sleep() for a few seconds to get the full screen effect  */

    mvaddstr(13, 33, "Hello, world!");
    refresh();
    sleep(3);


    /*  Clean up after ourselves  */

    delwin(mainwin);
    endwin();
    refresh();


}
#endif

int main(int argc, char* argv[])
{
#ifdef CURSES
  //  curses_print();
#endif
  auto game1 = std::unique_ptr<Game>(new Game());
  auto game2 = std::unique_ptr<Game>(new Game());

  return 0;
}
