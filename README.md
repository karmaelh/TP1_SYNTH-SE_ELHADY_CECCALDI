# TP1 Synthèse Système

## INTRODUCTION
Ce projet consiste à développer un mini-shell Enseash en langage C. Ce shell permet d'exécuter des commandes de base avec des fonctionnalités telles que la gestion des redirections d'entrée et de sortie, la mesure du temps d'exécution des commandes, et la gestion des erreurs. Ce document explique les objectifs, les fonctionnalités principales et les parties importantes du code ainsi que les problèmes rencontrés.

## OBJECTIFS DU PROJET

- Créer un shell permettant l'exécution de commandes utilisateur comme dans un terminal classique.
- Gérer les redirections d'entrée et de sortie pour manipuler les fichiers.
- Mesurer le temps d'exécution des commandes et afficher les codes de retour des processus enfant.
- Faciliter la lisibilité et la compréhension du code en suivant les bonnes pratiques de programmation.

## FONCTIONNALITÉS PRINCIPALES

Dans un premier temps, nous souhaitons présenter les fonctionnalités principales de notre code pour donner un premier aperçu de ce en quoi consiste notre projet.

### 1. Affichage interactif avec un prompt personnalisé

- Le shell affiche un prompt ("enseash %") en attente d'une commande utilisateur.

### 2. Exécution des commandes
Les commandes saisies sont analysées, et un processus enfant (à l'aide de "fork") est créé pour exécuter la commande via "execvp". En cas d'erreur (commande introuvable), un message est affiché.

### 3. Gestion des redirections (écriture et lecture)

- Le fichier question7.c gère les redirections :
  - `>` pour rediriger la sortie standard vers un fichier.
  - `<` pour rediriger l'entrée standard depuis un fichier.
- Les arguments associés aux redirections sont traités et retirés des arguments passés à la commande.

### 4. Mesure du temps d'exécution
- Le fichier "question5.c" calcule le temps d'exécution des commandes en millisecondes et l’affiche sur le terminal au format souhaité.

### 5. Affichage des codes de sortie et des signaux
- Les codes de retour ou signaux d'erreur (éventuellement causés par une interruption) sont affichés.


## PARTIES IMPORTANTES DU CODE

Nous allons mettre dans cette partie les parties de code qui nous sembles être les plus importantes au sein du projet par leur complexité et par le travail qu’elles nous ont demandé.

### 1. Fichier main.c

- Notre fichier main.c permet de gérer la boucle principale du shell, lire les commandes utilisateur avec "read" et créer des processus enfants via "fork" pour exécuter les commandes.
Fonctionnalités clés :
  - Gestion des erreurs (ex. fork ou commande introuvable).
  - Intégration des autres modules (redirection, mesure du temps).
  - Chaque fichier par question est inclus dans le main


### 2. Fichier question7.c : Gestion des redirections

- Nous avons eu du mal à écrire le code qui traite les deux cas spécifiques d’analyse des arguments pour la redirection d’entrée (<) et de sortie (>).

- D’abord, nous avons mis du temps avant de penser à utiliser la fonction dup2 car nous n’avions pas bien compris son fonctionnement avant.  Ici, on l’utilise (permet donc de manipuler les descripteurs de fichier) pour rediriger "stdout" ou "stdin" vers un fichier.

![Description de l'image 1](image/image1.png)

Ici, dup2 copie fd sur STDOUT_FILENO et de même pour STDIN_FILENO.

![Description de l'image 2](image/image2.png)


### 3. Fichier timer.c : Calcul du temps d'exécution
- Fonctions importantes :
  - "measure_execution_time" : Calcule le temps d'exécution en millisecondes.
  - "display_exit_code_with_time" : Affiche le code de sortie ou le signal avec le temps d'exécution.


## PROBLEMES RENCONTRES :

- Question 6 : plusieurs commandes ne marchaient pas sur Macos comme "-i" et "osfortune" il a donc fallu trouver des équiavlents pour pouvoir tester notre code comme "-s fortunes" et utiliser "brew install" pour installer les commandes nécessaires.
- Questions 1, 2, 3 : on a eu un problème de linker qui a ipliqué une modification du Makefile. Cela était dû au fait que nous avons fait un fichier différent pour chaque question pour rendre le code plus lisible et compréhensibe. 

## CONCLUSION
Ce projet constitue une introduction solide à la programmation système en C. Il couvre des concepts essentiels tels que la création de processus, la redirection des flux, et l'interaction utilisateur. Chaque module apporte une contribution importante à l'architecture globale, rendant le shell à la fois fonctionnel et extensible.

