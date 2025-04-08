#include "Ability.h"

std::string Ability::getName() {
	return this->_name;
};

int Ability::getPoints() {
	return this->_points;
};

int Ability::getDamage() {
	return this->_damage;
};
