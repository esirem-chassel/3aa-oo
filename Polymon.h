#pragma once
#include <string>
class Polymon
{
public:
	Polymon(std::string name, int speed, int hp);
	void addAttack(std::string name, int points, int damage);
	std::string getName();
private:
	std::string _name;
};

