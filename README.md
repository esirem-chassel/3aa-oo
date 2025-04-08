# Polymon

## Objectif de base

Nous allons créer un simulateur de combat entre créatures, les Polymon.
Deux classes vous sont fournies :
- Storage
- Polymon

`Storage` est une classe de stockage pour vos données. Pour notre exemple, nos Polymon seront stockés "en dur" dans le code.
La classe `Polymon` sera à compléter. Vous aurez d'autres classes à réaliser.

> [!Note]
> Tout votre code devra respecter les bonnes pratiques (encapsulation...) et être régulièrement mis à jour sur Github.
> Votre dépôt devra être nommé `3aa-oo` et votre enseignant doit y être ajouté en tout début de l'activité.
> Il est conseillé d'utiliser un `.gitignore` adapté.

> [!Caution]
> L'usage de votre poste personnel et d'Internet est autorisé.
> La communication vers d'autres personnes et l'usage d'outils d'Intelligence Artificielle sont interdits.

## Description du jeu de base

Dans votre classe principale, créez un simple menu comme nous avons fait dans d'autres TP pour permettre à l'utilisateur de choisir son Polymon parmi la liste.

Créez une classe Game, permettant de structurer une partie. Une partie de Polymon se joue à plusieurs manches.
Durant chaque manche, le Polymon initialement choisi par le joueur "combat" un Polymon choisit au hasard.
Le combat se déroule au tour par tour. A chaque tour, chaque polymon reçoit sa valeur en speed qui se cumule.
Puis, le joueur choisit une attaque parmi celles du Polymon, en dépensant des points de speed.
L'attaque réalise des dégâts au polymon adverse.
Ensuite, la meilleure attaque possible est choisie par votre programme pour le Polymon adverse (sur le même principe de speed).
La manche se termine quand la vie d'un des Polymon atteint zéro. A la fin de chaque manche, le Polymon du joueur récupère 10% de sa vie.
La partie se termine lorsque la vie du Polymon du joueur atteint zéro.

## Ajouts

> [!Warning]
> L'objectif est de réaliser un maximum d'éléments parmi les "Ajouts".
> Le "jeu de base" n'est que la partie minimale pour pouvoir travailler.

### Coup critique

Ajoutez un facteur aléatoire. A chaque attaque, il existe 5% de chances que le coup soit "critique" et inflige 150% de dégâts.

### Ability

Structurez les attaques en créant une classe "Ability". Un Polymon a une ou plusieurs compétences, qui ont un nom, un coût de speed, des dégâts infligés.
Créez également une classe "Ultimate", qui sont des "Ability" à fort coup, ne pouvant PAS réaliser de coup critique et qui n'ont aucun élément.

### Elements

Ajoutez une classe Element, qui contiendra un nom, ainsi qu'une référence vers un élément auquel cet élément est "fort" et un élément auquel cet élément est "faible".
Par exemple, "Feu" est fort contre "Glace" et faible contre "Eau".
Chaque Polymon possède un Element, et chaque Ability peut posséder un Element.
Si une attaque d'un Element est réalisé contre un Polymon d'un élément qui lui est "faible" (ex: attaque de feu contre Polymon de glace), alors elle inflige 200% de dégâts.
Si une attaque d'un Element est réalisé contre un Polymon d'un élément qui lui est "fort" (ex: attaque de feu contre Polymon d'eau), alors elle inflige 50% de dégâts.

# CORRIGE

## 1.0 - Complétion des classes et tests de base

On va commencer par compléter les classes qu'on a, et surtout : Polymon.
On comprend de l'énoncé et du code qu'un Polymon a un nom, une speed, des HP et une liste d'attaques.
Commençons par le .h qui manque les informations suivantes :

- speed, un entier
- hp, un entier
- attaques, une liste d'attaques

Pour ce dernier point, il nous faudra une structure pour "retenir" chaque attaque.
On va placer une string en attendant.

```cpp

class Polymon
{
public:
	Polymon(std::string name, int speed, int hp);
	void addAttack(std::string name, int points, int damage);
	std::string getName();
private:
	std::string _name;
	int _speed;
	int _hp;
	std::vector<std::string> _attacks = std::vector<std::string>();
};
```

Ensuite, complétons la partie cpp.
Encore une fois, pour le moment, on considère les attaques comme une liste de strings, mais on changera ça à terme.

```cpp
Polymon::Polymon(std::string name, int speed, int hp) {
	this->_name = name;
	this->_speed = speed;
	this->_hp = hp;
};

void Polymon::addAttack(std::string name, int points, int damage) {
	this->_attacks.push_back(name);
};

std::string Polymon::getName() {
	return this->_name;
};
```

Maintenant, pour respecter le principe d'encapsulation, nous allons créer les accesseurs (getters et setters) de Polymon.

Le .h d'abord, on indiquera d'ailleurs que les méthodes sont const, pour rester dans les bonnes pratiques.
```cpp
    std::string getName() const;
	int getSpeed() const;
	int getHp() const;
	std::vector<std::string> getAttacks() const;
```

Puis le .cpp :
```cpp
std::string Polymon::getName() const {
	return this->_name;
};

int Polymon::getSpeed() const {
	return this->_speed;
};

int Polymon::getHp() const {
	return this->_hp;
};

std::vector<std::string> Polymon::getAttacks() const {
	return this->_attacks;
};
```

Pour le moment on n'implantera pas les setters,
on ne devrait pas en avoir besoin de suite,
et on ne va pas changer les HP n'importe comment.

Testons notre programme principal,
tout d'abord pour lister nos Polymon et leurs attaques.

```cpp
#include <iostream>
#include "Storage.h"
#include "Polymon.h"

int main()
{
    std::cout << "P O L Y M O N" << std::endl;
    std::vector<Polymon> ls = Storage::getInstance()->getList();
    for (Polymon p : ls) {
        std::cout << "" << p.getName() << " | Speed : " << p.getSpeed() << " | HP : " << p.getHp() << std::endl;
        for (std::string atk : p.getAttacks()) {
            std::cout << "|| " << atk << std::endl;
        }
    }
}
```

Nous avons le minimum du minimum pour avancer.
On peut déjà prévoir certains soucis qui vont apparaître (speed, attaques...) mais avançons.

Créons d'abord la classe Game, comme demandé.
Cette classe va retenir le Polymon choisi,
ainsi que celui en cours d'affrontement,
la manche en cours, etc.

Comme on n'a pas besoin de pointeurs,
on peut enregistrer un Polymon et non un Polymon*,
mais C++ va refuser car aucun constructeur par défaut n'existe pour Polymon.

Rajoutons-en un !
Et assurons-nous que l'objet ne soit pas réellement utilisé,
donc plaçons notre constructeur en default.

```cpp
class Polymon
{
public:
	Polymon() = default;
	Polymon(std::string name, int speed, int hp);
```

Puis notre déclaration de Game :

```cpp
#pragma once
#include <iostream>
#include "Storage.h"
#include "Polymon.h"

class Game
{
public:
	Game();
private:
	Polymon _player;
	Polymon _against;
};
```

Et enfin une définition de base pour tester :
```cpp
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
```

On peut désormais tester notre programme très facilement :

```cpp
#include <iostream>
#include "Storage.h"
#include "Polymon.h"
#include "Game.h"

int main()
{
    std::cout << "P O L Y M O N" << std::endl;
    new Game();
}
```

On pourrait s'assurer qu'une seule instance de Game n'existe à un instant T
pour éviter les soucis, en utilisant un pattern Singleton.
On se garde l'idée pour plus tard.

Notre objectif maintenant est de :
- compléter la classe Game pour gérer les manches
- compléter les éventuels manques d'autres classes
- commencer à voir pour ajouter la partie "Ajouts"

Commençons par une méthode `bool jouerManche()` qui nous permettra de jouer
une manche et d'en retourner le résultat : `true` si le joueur gagne `false` sinon.
On ajoute également sur le même principe `int jouerTour();` qui jouera le tour courant,
et renverra 0 en cas de match nul, -1 en cas de défaite et 1 en cas de victoire.
Chacune de ces méthodes mutera les objets `_player` et `_against`.

Pour le moment, laissons les définitions de nos méthodes vides.
Pour jouer un tour, nous aurons besoin de :
- modifier les valeurs speed de nos Polymon
- modifier les valeurs HP de nos Polymon

Nous aurons donc besoin de setters,
et nous aurons besoin d'une propriété pour stocker,
sur un Polymon, son cumul de "speed" ou `_points`.

On fera bien attention à définir `_points` à zéro dans le .h :
c'est bien sa valeur de base et cela nous permet de conserver le constructeur tel quel.

Créons nos différents setters spécialisés :
```cpp
    void stackSpeed(); // appellé en début de tour, pour cumuler des points
	void usePoints(int pointsToUse); // usage des points
	void damageTaken(int taken); // dégâts encaissés
	void autoHeal(); // soins auto en fin de manche (10%)
	void reset(); // appellé en début de manche, remet à zéro les points
```

Ainsi que leurs définitions :
```cpp
void Polymon::stackSpeed() {
	this->_points += this->_speed;
};

// @TODO : what if not enough points ?
void Polymon::usePoints(int pointsToUse) {
	this->_points -= pointsToUse;
};

void Polymon::damageTaken(int taken) {
	this->_hp -= taken;
};

void Polymon::autoHeal() {
	this->_hp *= 1.1;
};

void Polymon::reset() {
	this->_points = 0;
};
```

On anticipe le souci des points insuffisants : on enverra une exception.

Puis, on implémente les différentes méthodes dans Game, pour gérer :
- chaque partie
- chaque manche
- chaque tour

```cpp
class Game
{
public:
	Game();
	void start();
	bool jouerManche();
	int jouerTour();
private:
	Polymon _player;
	Polymon _against;
	int _manche = 0;
};
```

La méthode pour chaque tour s'occupe uniquement de ce qu'il se passe dans un tour.
Pour le moment, nos attaques sont fictives.
Donc nous allons effectuer un random pour obtenir des dégâts et points aléatoires.

```cpp
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
```

Ensuite, la méthode pour gérer chaque manche ne s'intéresse qu'au contenu d'une manche.
C'est à dire le choix d'un Polymon adverse, le lancement des tours,
le reset des points du Polymon joueur,
ainsi que la conclusion de la manche.

```cpp
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
```

On lancera la partie via la méthode start(), qui bouclera tant que le Polymon joueur est "debout".

```cpp
void Game::start() {
    bool lastMancheResult = false;
    do {
        lastMancheResult = this->jouerManche();
    } while (lastMancheResult);
};
```
