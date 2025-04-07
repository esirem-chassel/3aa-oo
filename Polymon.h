#pragma once
#include <string>
#include <vector>

class Polymon
{
public:
	Polymon(std::string name, int speed, int hp);
	void addAttack(std::string name, int points, int damage);
	std::string getName();
private:
	std::string _name;
	int _speed;
	int _hp;
	std::vector<std::string> attaques = std::vector<std::string>();
};

