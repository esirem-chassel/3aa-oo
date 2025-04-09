#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "Ability.h"

class Polymon
{
public:
	Polymon() = default;
	Polymon(std::string name, int speed, int hp);
	void addAttack(std::string name, int points, int damage);
	std::string getName() const;
	int getSpeed() const;
	int getHp() const;
	std::vector<Ability> getAttacks() const;
	int getPoints() const;
	void reset();
	void stackSpeed();
	void usePoints(int pointsToUse);
	void damageTaken(int taken);
	void autoHeal();
	Ability getBestAbility();
private:
	std::string _name;
	int _speed;
	int _hp;
	int _points = 0;
	std::vector<Ability> _attacks = std::vector<Ability>();
};

