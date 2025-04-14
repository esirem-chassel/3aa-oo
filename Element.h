#pragma once
#include <string>
#include <unordered_map>

class Element
{
private:
	std::string _name;
	Element* _strongAgainst = nullptr;
	Element* _weakAgainst = nullptr;
public:
	static std::unordered_map<std::string, Element*> _elements;
	static Element* get(std::string name);
	static Element* forge(std::string name);
	Element(std::string name) : _name(name) {};
	std::string getName();
	void setStrength(Element* strong);
	void setWeakness(Element* weak);
	bool isStrongAgainst(Element* other);
	bool isWeakAgainst(Element* other);
};

