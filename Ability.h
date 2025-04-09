#pragma once
#include <string>

class Ability
{
private:
	std::string _name;
	int _points;
	int _damage;
public:
	Ability(std::string name, int points, int damage) : _name(name), _points(points), _damage(damage) {};
	std::string getName() const;
	int getPoints() const;
	int getDamage() const;
};

