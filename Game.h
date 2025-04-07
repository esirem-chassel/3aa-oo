#pragma once
#include <iostream>
#include "Storage.h"
#include "Polymon.h"

class Game
{
public:
	Game();
private:
	Polymon _player;
	Polymon _against;
};

