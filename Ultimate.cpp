#include "Ultimate.h"

Ultimate::Ultimate(std::string name, int points, int damage) {
	this->_name = name;
	this->_points = points;
	this->_damage = damage;
};

bool Ultimate::canCrit() const {
	return false;
};
