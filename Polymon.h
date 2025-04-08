#pragma once
#include <string>
#include <vector>

class Polymon
{
public:
	Polymon() = default;
	Polymon(std::string name, int speed, int hp);
	void addAttack(std::string name, int points, int damage);
	std::string getName() const;
	int getSpeed() const;
	int getHp() const;
	std::vector<std::string> getAttacks() const;
	void reset();
	void stackSpeed();
	void usePoints(int pointsToUse);
	void damageTaken(int taken);
	void autoHeal();
private:
	std::string _name;
	int _speed;
	int _hp;
	int _points = 0;
	std::vector<std::string> _attacks = std::vector<std::string>();
};

