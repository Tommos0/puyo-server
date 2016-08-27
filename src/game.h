#ifndef GAME_H
#define GAME_H
#include "playerstate.h"
#include <vector>
#include "point.h"
#include "curses_render.h"

class Game {
    public:
        Game(); 
        ~Game();
    const int BLOCK_EMPTY = 0;
    const int BLOCK_DOOM = -1;
private:
    CursesRender *cursesRender;
    bool lowerBlock(PlayerState *);
    void dropBlock(PlayerState *);
    bool removeHoles(PlayerState *);
    bool clearBlocks(PlayerState *);
    bool dropDoomblocks(PlayerState *);
    void newDroppingBlock(PlayerState *);
    std::vector<std::vector<point>> getChains(PlayerState *);
    std::vector<point> getChainForBlock(PlayerState *, int x, int y, std::vector<std::vector<bool>> checked );
    bool checkBounds(PlayerState *ps, int x, int y);

};


#endif /*GAME_H*/
