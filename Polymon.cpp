#include "Polymon.h"

Polymon::Polymon(std::string name, int speed, int hp) {
	this->_name = name;
	this->_speed = speed;
	this->_hp = hp;
};

void Polymon::addAttack(std::string name, int points, int damage) {
	this->_attacks.push_back(new Ability(name, points, damage));
};

void Polymon::addUltimate(std::string name, int points, int damage) {
	this->_attacks.push_back(new Ultimate(name, points, damage));
};

std::string Polymon::getName() const {
	return this->_name;
};

int Polymon::getSpeed() const {
	return this->_speed;
};

int Polymon::getHp() const {
	return this->_hp;
};

std::vector<Ability*> Polymon::getAttacks() const {
	return this->_attacks;
};

int Polymon::getPoints() const {
	return this->_points;
};

void Polymon::stackSpeed() {
	this->_points += this->_speed;
};

void Polymon::usePoints(int pointsToUse) {
	if (pointsToUse <= this->_points) {
		this->_points -= pointsToUse;
	} else {
		throw std::range_error("Not enough points !");
	}
};

void Polymon::damageTaken(int taken) {
	this->_hp -= taken;
};

void Polymon::autoHeal() {
	this->_hp *= 1.1;
};

void Polymon::reset() {
	this->_points = 0;
};

Ability* Polymon::getBestAbility() {
	Ability* found = nullptr;
	for (int i = this->_attacks.size() - 1; i >= 0; i--) {
		if ((found == nullptr)
			|| (this->_attacks[i]->getDamage() > found->getDamage())) {
			found = this->_attacks[i];
		}
	}
	if (found == nullptr) { // nothing found : get one randomly
		found = this->_attacks[0];
	}
	return found;
};
