#include <iostream>
#include "Storage.h"
#include "Polymon.h"
#include "Game.h"

int main()
{
    std::cout << "P O L Y M O N" << std::endl;
    Game* g = new Game();
    g->start();
}
