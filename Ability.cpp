#include "Ability.h"

std::string Ability::getName() const {
	return this->_name;
};

int Ability::getPoints() const {
	return this->_points;
};

int Ability::getDamage() const {
	return this->_damage;
};

bool Ability::canCrit() const {
	return true;
};
