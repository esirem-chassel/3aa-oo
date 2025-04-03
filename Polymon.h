#pragma once
#include <string>
class Polymon
{
public:
	Polymon(std::string name, int speed);
	void addAttack(std::string name, int points, int damage);
};

