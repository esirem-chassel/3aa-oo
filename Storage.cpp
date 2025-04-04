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
	Polymon feu = Polymon("Feufeu", 20, 800);
	Polymon glace = Polymon("Caille", 10, 900);
	Polymon eau = Polymon("Flotte", 18, 750);
	Polymon foudre = Polymon("Chok", 30, 500);
	Polymon terre = Polymon("Bimboom", 5, 1500);
	Polymon air = Polymon("Phew", 25, 600);
	feu.addAttack("Fire fire", 20, 100);
	feu.addAttack("Light the fire", 100, 600);
	glace.addAttack("Fepacho", 10, 100);
	glace.addAttack("Aglagla", 80, 900);
	eau.addAttack("Plouf", 15, 100);
	eau.addAttack("Groplouf", 95, 900);
	foudre.addAttack("Pika", 25, 120);
	foudre.addAttack("Chu", 100, 700);
	terre.addAttack("Bonk", 10, 90);
	terre.addAttack("Boom", 80, 800);
	air.addAttack("Swift", 10, 70);
	air.addAttack("PTSD", 110, 800);
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
