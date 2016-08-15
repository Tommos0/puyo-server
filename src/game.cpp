#include "game.h"
#include "gamestate.h"
#include <boost/thread/thread.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
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
    newDroppingBlock(gs);
    int ch;
    for (int i = 0; i<1000; i++) {
        boost::this_thread::sleep(boost::posix_time::milliseconds(20));
#ifdef CURSES
        
        if ((ch = cursesRender->getKey())) {
            cursesRender->debug(std::to_string(ch).c_str());
        }
        
        cursesRender->render(gs);
        
        if (gs->ticksWait > 0) {
            gs->ticksWait--;
            continue;
        }
        gs->ticksWait=10;
        if (!gs->blockDropped) {
            if (!lowerBlock(gs)) {
                dropBlock(gs);
            }
        } else {
            removeHoles(gs);
            if (clearBlocks(gs)) continue;
            if (dropDoomblocks(gs)) continue;
            newDroppingBlock(gs);
        }
#endif
    }
    
#ifdef CURSES
    delete cursesRender;
#endif
    
}

bool Game::lowerBlock(GameState *gs) {
    for (int x=0; x<2; x++) for (int y=0; y<2; y++) {
        if (gs->droppingBlock[x][y]>0 && ((gs->droppingBlockY+y-1 < 0) || (gs->field[gs->droppingBlockX+x][gs->droppingBlockY+y-1]>0)))
        {
            return false;
        }
    }
    gs->droppingBlockY--;
    return true;
}

void Game::dropBlock(GameState *gs) {
    for (int x=0; x<2; x++) for (int y=0; y<2; y++) {
        if (gs->droppingBlock[x][y] > 0)
            gs->field[gs->droppingBlockX+x][gs->droppingBlockY+y] = gs->droppingBlock[x][y];
    }
    gs->blockDropped = true;
}

bool Game::removeHoles(GameState *gs) {
    return false;
}

bool Game::clearBlocks(GameState *gs) {
    return false;
}

bool Game::dropDoomblocks(GameState *gs) {
    return false;
}

void Game::newDroppingBlock(GameState *gs) {
    gs->blockDropped = false;
    gs->droppingBlockX = 5;
    gs->droppingBlockY = 28;
    gs->droppingBlock[0][0] = 0;
    gs->droppingBlock[1][0] = 0;
    gs->droppingBlock[0][1] = rand()%4+1;
    gs->droppingBlock[1][1] = rand()%4+1;
}

Game::~Game() {
    std::cout << "game destroyed" << std::endl;
}


