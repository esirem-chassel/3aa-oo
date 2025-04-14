#include "Element.h"

std::unordered_map<std::string, Element*> Element::_elements = std::unordered_map<std::string, Element*>();

Element* Element::get(std::string name) {
	Element* r = nullptr;
	auto e = Element::_elements.find(name);
	if (e != Element::_elements.end()) {
		r = e->second;
	}
	return r;
};

Element* Element::forge(std::string name) {
	Element* e = new Element(name);
	Element::_elements.emplace(name, e);
	return e;
};

std::string Element::getName() {
	return this->_name;
};

void Element::setStrength(Element* strong) {
	this->_strongAgainst = strong;
};

void Element::setWeakness(Element* weak) {
	this->_weakAgainst = weak;
};

bool Element::isStrongAgainst(Element* other) {
	return (this->_strongAgainst->getName() == other->getName());
};

bool Element::isWeakAgainst(Element* other) {
	return (this->_weakAgainst->getName() == other->getName());
};
