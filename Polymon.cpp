#include "Polymon.h"

Polymon::Polymon(std::string name, int speed, int hp) {
	this->_name = name;
	this->_speed = speed;
	this->_hp = hp;
};

void Polymon::addAttack(std::string name, int points, int damage) {
	this->_attacks.push_back(name);
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

std::vector<std::string> Polymon::getAttacks() const {
	return this->_attacks;
};

void Polymon::stackSpeed() {
	this->_points += this->_speed;
};

// @TODO : what if not enough points ?
void Polymon::usePoints(int pointsToUse) {
	this->_points -= pointsToUse;
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

