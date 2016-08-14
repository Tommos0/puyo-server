#ifndef GAME_H
#define GAME_H
#include "gamestate.h"
class Game {
    public:
        Game(); 
        ~Game();
private:
    bool lowerBlock(GameState *);
    void dropBlock(GameState *);
    bool removeHoles(GameState *);
    bool clearBlocks(GameState *);
    bool dropDoomblocks(GameState *);
    void newDroppingBlock(GameState *);
};


#endif /*GAME_H*/
