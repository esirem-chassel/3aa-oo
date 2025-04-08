#pragma once
#include <iostream>
#include <stdexcept>
#include "Storage.h"
#include "Polymon.h"

class Game
{
public:
	Game();
	void start();
	bool jouerManche();
	int jouerTour();
private:
	Polymon _player;
	Polymon _against;
	int _manche = 0;
};

