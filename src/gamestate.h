#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
public:
    GameState(int, int);
    ~GameState();
    int sizex;
    int sizey;
    short **field;

private:
    long tick;
};


#endif /*GAMESTATE_H*/
