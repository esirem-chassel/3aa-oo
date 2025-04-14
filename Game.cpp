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

    this->playerTurn();
    if (this->_against.getHp() <= 0) {
        this->foeTurn();
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

void Game::playerTurn() {
    std::vector<Ability*> playerAbilities = this->_player.getAttacks();
    int userChoice = -1;

    do {
        std::cout << "Selectionnez votre attaque (" << this->_player.getPoints() << " SP disponibles) :" << std::endl;
        int ix = 0;
        std::cout << "[-1] Passer" << std::endl;
        for (Ability* a : playerAbilities) {
            if (a->getPoints() <= this->_player.getPoints()) {
                std::cout << "[ " << std::to_string(ix) << "] " << a->getName() << "(" << a->getPoints() << ")" << std::endl;
            }
            ix++;
        }
        std::cin >> userChoice;
    } while ((userChoice > 0) && (userChoice > playerAbilities.size()));
    if (userChoice >= 0) {
        Ability* playerUsed = playerAbilities[userChoice];
        this->tryAttack(&this->_player, &this->_against, playerUsed, false);
    }
};

void Game::foeTurn() {
    Ability* foeUsed = this->_against.getBestAbility();
    this->tryAttack(&this->_against, &this->_player, foeUsed, true);
};

void Game::tryAttack(Polymon* src, Polymon* trg, Ability* attack, bool foeAgainstPlayer) {
    std::string srcName = foeAgainstPlayer ? "Le polymon adverse" : "Votre polymon";
    std::string trgName = foeAgainstPlayer ? "Votre polymon" : "Le polymon adverse";

    int pointsUsed = attack->getPoints();
    bool isCrit = attack->canCrit() && (5 >= (std::rand() % 100 + 1));

    try {
        std::cout << srcName << " utilise " << attack->getName() << " !" << std::endl;
        src->usePoints(pointsUsed);
        int damageTaken = attack->getDamage();
        if (isCrit) {
            std::cout << "Coup critique ! ";
            damageTaken *= 1.5;
        }
        Element* abilityElement = attack->getElement();
        if (nullptr != abilityElement) {
            if (abilityElement->isStrongAgainst(trg->getElement())) {
                std::cout << " C'est tres efficace ! ";
                damageTaken *= 2;
            }
            else if (abilityElement->isWeakAgainst(trg->getElement())) {
                std::cout << " C'est peu efficace... ";
                damageTaken *= 0.5;
            }
        }
        std::cout << trgName << " prends " << std::to_string(damageTaken) << " ! ";
        trg->damageTaken(damageTaken);
        std::cout << "(HP restants : " << std::to_string(trg->getHp()) << ")" << std::endl;
    }
    catch (const std::range_error e) {
        std::cout << srcName << " est a court d'energie ("
            << std::to_string(src->getPoints())
            << " / "
            << std::to_string(pointsUsed)
            << ") !" << std::endl;
    }
};
