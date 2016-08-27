#ifndef GAMESTATE_H
#define GAMESTATE_H

class PlayerState {
public:
    PlayerState(int, int);
    ~PlayerState();
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
