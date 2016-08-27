#include "game.h"
#include "playerstate.h"
#include <boost/thread/thread.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include "point.h"

#ifdef CURSES
    #include "curses_render.h"
#endif

Game::Game() {
    PlayerState *gs  = new PlayerState(10,30);
    //PlayerState *gs2 = new PlayerState(10,20);

    
    std::cout << "game created" << std::endl;
    
#ifdef CURSES
    cursesRender = new CursesRender();
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

bool Game::lowerBlock(PlayerState *gs) {
    for (int x=0; x<2; x++) for (int y=0; y<2; y++) {
        if (gs->droppingBlock[x][y]>0 && ((gs->droppingBlockY+y-1 < 0) || (gs->field[gs->droppingBlockX+x][gs->droppingBlockY+y-1]>0)))
        {
            return false;
        }
    }
    gs->droppingBlockY--;
    return true;
}

void Game::dropBlock(PlayerState *gs) {
    for (int x=0; x<2; x++) for (int y=0; y<2; y++) {
        if (gs->droppingBlock[x][y] > 0)
            gs->field[gs->droppingBlockX+x][gs->droppingBlockY+y] = gs->droppingBlock[x][y];
    }
    gs->blockDropped = true;
}

bool Game::removeHoles(PlayerState *gs) {
    return false;
}

bool Game::clearBlocks(PlayerState *gs) {
    auto a = getChains(gs);
    return false;
}

bool Game::dropDoomblocks(PlayerState *gs) {
    return false;
}

void Game::newDroppingBlock(PlayerState *gs) {
    gs->blockDropped = false;
    gs->droppingBlockX = 5;
    gs->droppingBlockY = 28;
    gs->droppingBlock[0][0] = 0;
    gs->droppingBlock[1][0] = 0;
    gs->droppingBlock[0][1] = rand()%2+1;
    gs->droppingBlock[1][1] = rand()%2+1;
}

bool Game::checkBounds(PlayerState *ps, int x, int y) {
    return !(x<0 || x>ps->sizex || y<0 || y>ps->sizey);
}

std::vector<point> Game::getChainForBlock(PlayerState * ps, int x, int y, std::vector<std::vector<bool>> checked ) {
    checked[x][y] = true;
    int neighbourOffsets[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    std::vector<point> points;
    point p;
    p.x=x; p.y=y;
    points.push_back( p );
    short color = ps->field[x][y];
    for (int i=0; i<4; i++) {
        point nb;
        nb.x = x + neighbourOffsets[i][0];
        nb.y = y + neighbourOffsets[i][1];
        if (checkBounds(ps, nb.x, nb.y)) {
            if (ps->field[nb.x][nb.y] == color) {
                std::vector<point> joins = getChainForBlock(ps, nb.x, nb.y, checked);
                points.insert(points.end(), joins.begin(), joins.end());
            }
        }
    }
    return points;
}

std::vector<std::vector<point>> Game::getChains(PlayerState * ps) {
    std::vector<std::vector<bool>> checked = std::vector<std::vector<bool>>(ps->sizex, std::vector<bool>(ps->sizey));
    std::vector<std::vector<point>> chains;
    for (int x=0; x<ps->sizex; x++) for (int y=0; y<ps->sizey; y++) {
        if (ps->field[x][y] != BLOCK_EMPTY && ps->field[x][y] != BLOCK_DOOM && !checked[x][y]) {
            std::vector<point> chain = getChainForBlock(ps,x,y,checked);
            chains.push_back(chain);
        }
    }
    cursesRender->debug(std::to_string(chains.size()).c_str());
    return chains;
}


Game::~Game() {
    std::cout << "game destroyed" << std::endl;
}


