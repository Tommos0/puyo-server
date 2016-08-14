#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
public:
    GameState(int, int);
    ~GameState();
    int sizex;
    int sizey;
    short **field;
    short **droppingBlock;
    int droppingBlockX;
    int droppingBlockY;
    int *doomBlocks;
    bool blockDropped;
    int ticksWait;
private:
    long tick;
};


#endif /*GAMESTATE_H*/
