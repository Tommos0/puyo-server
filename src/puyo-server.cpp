#include <cstdlib>
#include <iostream>
#include <memory>
//#include "network.h"
#include "game.h"

int main(int argc, char* argv[])
{

  auto game1 = std::unique_ptr<Game>(new Game());
  return 0;
}
