#include "Game.h"

Game::Game() {
	// on demande d'abord à l'utilisateur son Polymon
    std::vector<Polymon> ls = Storage::getInstance()->getList();
    int choice;
    int ix;
    do {
        ix = 0;
        for (Polymon p : ls) {
            std::cout << "[" << std::to_string(++ix) << "] " << p.getName() << std::endl;
        }
        std::cin >> choice;
    } while ((choice <= 0) or (choice > ls.size()));
    this->_player = ls[choice - 1];


    this->_against = Storage::getInstance()->pickRandom();

    std::cout << "Chosen one : " << this->_player.getName() << std::endl;
    std::cout << "AGAINST : " << this->_against.getName() << std::endl;

};
