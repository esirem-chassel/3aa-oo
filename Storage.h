#pragma once
#include <vector>
#include <ctime>
#include "Polymon.h"

class Storage
{
private:
	static Storage* _instance;
	Storage();
	void initData();
	std::vector<Polymon> db;
public:
	static Storage* getInstance();
	Polymon pickRandom();
};

