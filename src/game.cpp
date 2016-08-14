#include "game.h"
#include "gamestate.h"
#include <boost/thread/thread.hpp>
#include <iostream>

#ifdef CURSES
    #include "curses_render.h"
#endif

Game::Game() {
    GameState *gs  = new GameState(10,30);
    //GameState *gs2 = new GameState(10,20);

    
    std::cout << "game created" << std::endl;
    
#ifdef CURSES
    CursesRender *cursesRender = new CursesRender();
#endif
    
    for (int i = 0; i<1000; i++) {
        boost::this_thread::sleep(boost::posix_time::milliseconds(10));
#ifdef CURSES
        gs->field[5][29] = i%10;
        cursesRender->render(gs,2,10);
#endif
    }
    
#ifdef CURSES
    delete cursesRender;
#endif
    
}
Game::~Game() {
    std::cout << "game destroyed" << std::endl;
}


