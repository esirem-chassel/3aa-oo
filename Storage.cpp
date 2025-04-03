#include "Storage.h"

Storage* Storage::_instance = nullptr;

Storage* Storage::getInstance() {
	if (nullptr == Storage::_instance) {
		Storage::_instance = new Storage();
	}
	return Storage::_instance;
};

Storage::Storage() {
	std::srand(std::time(0));
};

void Storage::initData() {
	Polymon feu = Polymon("Feufeu", 10);
	Polymon glace = Polymon("Caille", 10);
	Polymon eau = Polymon("Flotte", 10);
	Polymon foudre = Polymon("Chok", 10);
	Polymon terre = Polymon("Bimboom", 10);
	Polymon air = Polymon("Phew", 10);
	feu.addAttack("Fire fire", 10, 10);
	feu.addAttack("Light the fire", 100, 200);
	this->db.push_back(feu);
	this->db.push_back(glace);
	this->db.push_back(eau);
	this->db.push_back(foudre);
	this->db.push_back(terre);
	this->db.push_back(air);
};

Polymon Storage::pickRandom() {
	int r = std::rand() % this->db.size() + 1;
	return this->db[r];
};
