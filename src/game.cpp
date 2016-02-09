#include "game.h"
#include <iostream>
Game::Game() {
    field = new short*[10];
    for (int i=0;i<10;i++) {
        field[i] = new short[20];
    }
    
    std::cout << "game created" << std::endl;

}
Game::~Game() {
    
    std::cout << "game destroyed" << std::endl;
}


