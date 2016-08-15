#include "gamestate.h"
#include <iostream>
GameState::GameState(int sizex, int sizey) {
    this->sizex = sizex;
    this->sizey = sizey;
    field = new short*[sizex];
    for (int i=0;i<sizex;i++) {
        field[i] = new short[sizey] ();
    }
    droppingBlock = new short*[2];
    droppingBlock[0] = new short[2] ();
    droppingBlock[1] = new short[2] ();
    blockDropped = false;
    doomBlocks = new int[sizex] ();
    tick = 0;
    ticksWait = 0;
//    memset(field,0,sizeof(int)*sizex*sizey);
    std::cout << "gamestate created" << std::endl;
    
}
GameState::~GameState() {
    
    std::cout << "gamestate destroyed" << std::endl;
}


