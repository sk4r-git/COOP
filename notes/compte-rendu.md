# 6/12/23

- Lancer l'itop sur notre POC pour voir s'il y a la prise en compte de l'overlapping.
Si présent regarder le z3 pour pouvoir l'optimiser.
Sinon, voir pour l'ajouter à l'itop.

- Essayer de comprendre pourquoi le CFI de clang fait planter le programme.
(Afin de voir si on peut le faire fonctionner dans LLVM).

- Pour l'implémentation de l'overlapping:
	1. Soit automatisation de bout en bout (avec z3).
	2. Soit automatisation qui va aider l'attaquant à faire son overlapping (en présentant à  l'attaquant des petits bouts de code déjà construits).

Pour calculer l'overlap on a besoin d'extraire la liste des gadgets.

- Essayer de "pièger" les tests pour l'iTOP pour avoir les points à observer.

- Décomposer le pipeline pour voir si y a des bouts utilisables par un humain.

# 19/12/23

Présentation de l'exploit

L'itop ne fonctionne pas sur notre exploit
Raisonnment symbolique (besoin de faire une analyse sémantique en amont)
AngR utilise l'assembleur de PyVex pour faire de l'analyse logique.

Regarder comment dans l'itop, AngR utilise PyVex

1. Trouver d'autres exemples pour vérifier les limites d'itop
2. Regarder l'utilisation d'AngR par l'itop
3. Faire un encodage de l'overlapping (on peut le passer à z3 -> trouve moi une chaine qui soit vrai, mais à quel coût?)

1. Chercher des idées sans forcément se baser sur les méthodes sémantiques

/!\ Noter les tentatives même celles qui échouent

# 25/01/23

Dans la présentation expliquer précisément pourquoi leur truc ne marche pas
-> limitation réelle et limitation technique

Pour comprendre pourquoi ça ne marche pas, pouvoir détruire à chaque étape (et savoir bien l'expliquer)
Expliquer à chaque étape les hypothèses qui ne sont pas dites (pourquoi dans leur cas ça marche, process en profondeur) et pourquoi ça ne marche pas
Donner des solutions de comment on pourrait améliorer ça (alternative ou même exemple)

Si après ce travail d'analyse, il nous reste du temps, on peut coder un backend pour z3
Trouver un test qui passe chez eux

Parallèliser le travail -> debunk + regarder ou ça coince dans le pipeline

Question sur la partie symbolique

Dans le papier, ils compilent les gadgets puis les passent dans z3. Voir si dans le code ils font bien ça ou s'ils demandent à z3 de trouver une combinaison de gadgets.
Essayer d'intercepter les appels à z3 et comprendre ce qu'ils font
