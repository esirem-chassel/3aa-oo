# Polymon

## Objectif de base

Nous allons créer un simulateur de combat entre créatures, les Polymon.
Deux classes vous sont fournies :
- Storage
- Polymon

Storage est une classe de stockage pour vos données. Pour notre exemple, nos Polymon seront stockés "en dur" dans le code.
La classe Polymon sera à compléter. Vous aurez d'autres classes à réaliser.

> [!Note]
> Tout votre code devra respecter les bonnes pratiques (encapsulation...) et être régulièrement mis à jour sur Github.

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

