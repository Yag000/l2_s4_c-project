Projet de C du S4 de la licence d'informatique (par Yago Iglesias Vazquez et Gabin Dudillieu)

Tout d'abord, pour compiler le projet, il faut utiliser la commande :

$make main

Puis pour lancer le programme, il faut utiliser la commande :

$./main text.txt

Le résultat s'affichera alors dans le terminal courant.

On met à disposition aussi plusieurs flags pour l'execution du main :
(le fichier texte doit toujours rester en 1ère position si le main en requiert un)

"-i" qui permet de prendre en entrée le terminal courant au lieu d'un fichier texte (si un fichier texte est donné en première position, ce flag est ignoré, et vous pouvez utiliser la commande "exit" pour en sortir).
"-v" qui permet d'afficher la commande, en plus de l'affichage de base (couplé avec le "-i", ce flag est ignoré).
"-c" qui permet de continuer la lecture du texte, même après une erreur qui ne nécéssite pas l'arrêt du programme (une erreur de chemin par exemple).
"-o=output.txt" qui permet, en remplaçant "output.txt" par un fichier de sortie, d'afficher les résultats des commandes dans ce fichier au lieu du terminal courant (si le fichier n'existe pas, il est alors créé si c'est possible)
"-r=input.txt" qui permet, en remplaçant "input.txt" par un fichier de sortie, d'afficher les entrées de commandes dans cet output, enregistrant donc un nouvel input (si le fichier n'existe pas, il est alors créé si c'est possible).


Vous pouvez lancer une batterie de tests, qui va vérifier si le code compile bien, si les tests unitaires réussissent, et si tout les résultats (outputs) des entrées donnés (inputs) correspondent à ceux attendus (expected_output) (Il n'est pas nécessaire de compiler les tests unitaires, le programme le fera seul).
Pour cela, il faut utiliser la commande :

$./test.sh

On met aussi à disposition plusieurs flags pour l'execution de ces tests :

"-v" qui affiche plus de détails sur les tests unitaires.
"--valgrind" qui lance les test avec valgrind.
"--only-main" qui lance seulement les tests de main.
"--only-unit" qui lance seulement les tests unitaires.
"--help" ou "-h" qui affiche une explication des options.

Il est aussi possible de compiler et lancer seulement les tests unitaires, en utilisant la commande :

$make test && ./test

À noter que vous pouvez ajouter "-v" à la fin aussi pour afficher plus de détails sur les tests unitaires effectués.


Enfin, pour supprimer ce qui a été compilé, il faut utiliser la commande :

$make clean


Pour les autres ajouts :

Dans les inputs donnés, les chemins doivent respecter la forme donnée dans les consignes de projet.
Il est possible néanmoins d'utiliser, autant de fois que possible, les noms "." qui permet de sélectionner le noeud courant, et ".." qui permet de sélectionner le parent du noeud courant.

Enfin, pour les commandes suivantes : "ls", "mkdir` et "touch", il est possible, en plus des demandes du projet, de leur donner des chemins complets en argument.
