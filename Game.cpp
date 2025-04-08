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
};

void Game::start() {
    bool lastMancheResult = false;
    do {
        lastMancheResult = this->jouerManche();
    } while (lastMancheResult);
};

bool Game::jouerManche() {
    bool r = false;
    this->_manche++;
    this->_player.reset();
    this->_against = Storage::getInstance()->pickRandom();
    std::cout << "Manche "
              << std::to_string(this->_manche)
              << " : " << this->_player.getName()
              << " VS " << this->_against.getName() << std::endl;
    int lastTourResult = 0;
    while (lastTourResult == 0) {
        lastTourResult = this->jouerTour();
    }
    if (lastTourResult < 0) {
        std::cout << "Votre adversaire vous a mis KO !" << std::endl;
        r = false; // perdu !
    }
    else {
        std::cout << "Votre adversaire est KO !" << std::endl;
        this->_player.autoHeal();
        r = true; // gagne !
    }
    return r;
};

int Game::jouerTour() {
    this->_player.stackSpeed();

    int damageTaken = std::rand() % 500 + 1;
    int damageDone = std::rand() % 500 + 1;

    int pointsUsedPlayer = std::rand() % 20 + 1;
    int pointsUsedAgainst = std::rand() % 20 + 1;

    std::cout << "Vous prenez " << std::to_string(damageTaken) << " ! ";
    this->_against.usePoints(pointsUsedAgainst);
    this->_player.damageTaken(damageTaken);
    std::cout << "(HP restants : " << std::to_string(this->_player.getHp()) << ")" << std::endl;
    std::cout << "Vous infligez " << std::to_string(damageDone) << " ! ";
    this->_player.usePoints(pointsUsedPlayer);
    this->_against.damageTaken(damageDone);
    std::cout << "(HP restants : " << std::to_string(this->_against.getHp()) << ")" << std::endl;

    if (this->_player.getHp() <= 0) {
        return -1;
    }
    else if (this->_against.getHp() <= 0) {
        return 1;
    }
    else {
        return 0;
    }
};
