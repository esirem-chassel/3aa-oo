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
	this->initData();
};

void Storage::initData() {
	Element* e_feu = Element::forge("feu");
	Element* e_eau = Element::forge("eau");
	Element* e_glace = Element::forge("glace");
	Element* e_terre = Element::forge("terre");
	Element* e_foudre = Element::forge("foudre");
	Element* e_air = Element::forge("air");
	e_feu->setStrength(e_glace);
	e_feu->setWeakness(e_eau);
	e_eau->setStrength(e_foudre);
	e_eau->setStrength(e_feu);
	e_glace->setStrength(e_eau);
	e_terre->setStrength(e_foudre);
	e_foudre->setStrength(e_eau);
	e_foudre->setStrength(e_air);
	e_foudre->setWeakness(e_terre);
	e_air->setStrength(e_feu);
	Polymon feu = Polymon("Feufeu", 20, 800, e_feu);
	Polymon glace = Polymon("Caille", 10, 900, e_glace);
	Polymon eau = Polymon("Flotte", 18, 750, e_eau);
	Polymon foudre = Polymon("Chok", 30, 500, e_foudre);
	Polymon terre = Polymon("Bimboom", 5, 1500, e_terre);
	Polymon air = Polymon("Phew", 25, 600, e_air);
	feu.addAttack("Fire fire", 20, 100, e_feu);
	feu.addAttack("Light the fire", 100, 600, e_feu);
	feu.addUltimate("TOUCRAMER", 200, 2000);
	glace.addAttack("Fepacho", 10, 100, e_glace);
	glace.addAttack("Aglagla", 80, 900, e_glace);
	eau.addAttack("Plouf", 15, 100, e_eau);
	eau.addAttack("Groplouf", 95, 900, e_eau);
	foudre.addAttack("Pika", 25, 120, e_foudre);
	foudre.addAttack("Chu", 100, 700, e_foudre);
	terre.addAttack("Bonk", 10, 90, e_terre);
	terre.addAttack("Boom", 80, 800);
	air.addAttack("Swift", 10, 70, e_air);
	air.addAttack("PTSD", 110, 800);
	this->db.push_back(feu);
	this->db.push_back(glace);
	this->db.push_back(eau);
	this->db.push_back(foudre);
	this->db.push_back(terre);
	this->db.push_back(air);
};

Polymon Storage::pickRandom() {
	int r = -1;
	while ((r < 0) or (r >= this->db.size())) {
		r = std::rand() % this->db.size() + 1;
	}
	return this->db[r];
};

std::vector<Polymon> Storage::getList() {
	return this->db;
};
