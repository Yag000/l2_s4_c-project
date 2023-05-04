#Projet de C du S4 de la licence d'informatique
**(par Yago Iglesias Vazquez et Gabin Dudillieu)**

## Compilation et lancement du main

Tout d'abord, pour compiler le projet, il faut utiliser la commande :

```bash
$make main
```

Puis pour lancer le programme, il faut utiliser la commande :

```bash
$./main text.txt
```

Le résultat s'affichera alors dans le terminal courant.

On met à disposition aussi plusieurs flags pour l'exécution du main _(le fichier texte doit toujours rester en 1ère position si le main en requiert un)_:

`-i` qui permet de prendre en entrée le terminal courant au lieu d'un fichier texte (si un fichier texte est donné en première position, ce flag est ignoré, et vous pouvez utiliser la commande `exit` pour en sortir).

`-v` qui permet d'afficher la commande, en plus de l'affichage de base (couplé avec le le flag `-i`, ce flag est ignoré).

`-c` qui permet de continuer la lecture du texte, même après une erreur qui ne nécéssite pas l'arrêt du programme (une erreur de chemin par exemple).

`-o=output.txt` qui permet en remplaçant "output.txt" par un fichier de sortie, d'afficher les résultats des commandes dans cet output au lieu du termianl courant (si le fichier n'existe pas, il est alors créer si c'est possible).

## Compilation et lancement des tests

Pour compiler les tests, il faut utiliser la commande :

```bash
$make test
```

Puis pour run les tests, il faut utiliser la commande :

```bash
$./test.sh
```

_À noter que vous pouvez ajouter `-v` à la fin pour afficher plus de détails sur les tests effectués._

Enfin, pour supprimer ce qui a été compilé, il faut utiliser la commande :

```bash
$make clean
```
