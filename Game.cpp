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

    this->_player.damageTaken(-10000); // on triche
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
    this->_against.stackSpeed();

    std::vector<Ability> playerAbilities = this->_player.getAttacks();
    std::vector<Ability> foeAbilities = this->_against.getAttacks();

    int indexPlayerAttack = -1;
    while ((indexPlayerAttack < 0) or (indexPlayerAttack >= playerAbilities.size())) {
        indexPlayerAttack = std::rand() % playerAbilities.size();
    }

    Ability foeUsed = this->_against.getBestAbility();

    int pointsUsedPlayer = playerAbilities[indexPlayerAttack].getPoints();
    int pointsUsedAgainst = foeUsed.getPoints();

    try {
        std::cout << "Votre adversaire utilise " << foeUsed.getName() << " !" << std::endl;
        this->_against.usePoints(pointsUsedAgainst);
        int damageTaken = foeUsed.getDamage();
        std::cout << "Vous prenez " << std::to_string(damageTaken) << " ! ";
        this->_player.damageTaken(damageTaken);
        std::cout << "(HP restants : " << std::to_string(this->_player.getHp()) << ")" << std::endl;
    }
    catch (const std::range_error e) {
        std::cout << "Le polymon adverse est a court d'energie ("
            << std::to_string(this->_against.getPoints())
            << " / "
            << std::to_string(pointsUsedAgainst)
            << ") !" << std::endl;
    }
    
    try {
        std::cout << "Vous utilisez " << playerAbilities[indexPlayerAttack].getName() << " !" << std::endl;
        this->_player.usePoints(pointsUsedPlayer);
        int damageDone = playerAbilities[indexPlayerAttack].getDamage();
        std::cout << "Vous infligez " << std::to_string(damageDone) << " ! ";
        this->_against.damageTaken(damageDone);
        std::cout << "(HP restants : " << std::to_string(this->_against.getHp()) << ")" << std::endl;
    }
    catch (const std::range_error e) {
        std::cout << "Votre Polymon est a court d'energie ("
            << std::to_string(this->_player.getPoints())
            << " / "
            << std::to_string(pointsUsedPlayer)
            << ") !" << std::endl;
    }

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
