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

## Complétion des classes et tests de base

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
