#pragma once
#include <string>
#include "Element.h"

class Ability
{
protected:
	Ability() = default;
	std::string _name;
	int _points;
	int _damage;
	Element* _element = nullptr;
public:
	Ability(std::string name, int points, int damage) : _name(name), _points(points), _damage(damage) {};
	std::string getName() const;
	int getPoints() const;
	int getDamage() const;
	virtual bool canCrit() const;
	void setElement(Element* element);
	Element* getElement() const;
};

