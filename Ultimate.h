#pragma once
#include "Ability.h"

class Ultimate : public Ability
{
public:
	Ultimate(std::string name, int points, int damage);
	bool canCrit() const override;
};

