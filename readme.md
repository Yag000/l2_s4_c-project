# Projet de C du S4 de la licence d'informatique

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

On met à disposition aussi plusieurs flags pour l'exécution du main _(le fichier texte doit toujours rester en première position, sauf pour l'utilisation de `-i`)_ :

- `-i` qui permet de prendre en entrée le terminal courant au lieu d'un fichier texte _(si un fichier texte est donné en première position, ce flag est ignoré)_. Cette option doit toujours être mise en **première position**. Vous pouvez utiliser la commande `exit` pour en sortir.

- `-v` qui permet d'afficher la commande, en plus de l'affichage de base donnés par la commande _(couplé avec le le flag `-i`, ce flag est ignoré)_.

- `-c` qui permet de continuer la lecture du texte, même après une erreur qui ne nécessite pas l'arrêt du programme _(une erreur de chemin par exemple)_.

- `-o=output.txt` qui permet, en remplaçant "output.txt" par un fichier de sortie, d'afficher les résultats des commandes dans ce fichier au lieu du terminal courant _(si le fichier n'existe pas, il est alors créé si c'est possible)_.

- `-r=input.txt` qui permet, en remplaçant "input.txt" par un fichier de sortie, d'afficher les entrées de commandes dans cet output, enregistrant donc un nouvel input _(si le fichier n'existe pas, il est alors créé si c'est possible)_.

## Compilation et lancement des tests

Vous pouvez lancer une batterie de tests, qui va vérifier si le code compile bien, si les tests unitaires réussissent, et si tout les résultats _(outputs)_ des entrées donnés _(inputs)_ correspondent à ceux attendus _(expected_output)_ _(Il n'est pas nécessaire de compiler les tests unitaires, le programme le fera seul)_.

Pour cela, il est possible d'utiliser la commande :

```bash
$./test.sh
```

On met aussi à disposition plusieurs flags pour l'execution de cette batterie de tests :

- `-v` qui affiche plus de détails sur les tests unitaires donnés.
- `--valgrind` qui lance les test avec valgrind.
- `--only-main` qui lance seulement les tests de main.
- `--only-unit` qui lance seulement les tests unitaires.
- `--help` ou `-h` qui affiche une explication des options.

Vous pouvez aussi compiler et lancer seulement les tests unitaires, en utilisant la commande :

```bash
$make test && ./test
```

_À noter que vous pouvez ajouter `-v` à la fin pour afficher plus de détails sur les tests unitaires effectués._

## Supprimer les fichiers compilés

Pour supprimer ce qui a été compilé, il faut utiliser la commande :

```bash
$make clean
```

## Autres ajouts

Dans les inputs donnés, les chemins doivent respecter la forme donnée dans les consignes de projet.

Néanmoins, dans notre projet, il est possible d'utiliser, autant de fois que possible, les noms `.`, qui permet de sélectionner le noeud courant, et `..`, qui permet de sélectionner le parent du noeud courant.

Nous avons implémenté une commande de plus, `echo`, qui permet d'afficher un message dans le terminal courant. Cette commande peut prendre un nombre indéfini d'arguments, et affichera alors tous les arguments donnés, séparés par un espace.

Enfin, pour les commandes suivantes : `ls`, `mkdir` et `touch`, il est possible, en plus des demandes du projet, de leur donner des chemins complets en argument.
