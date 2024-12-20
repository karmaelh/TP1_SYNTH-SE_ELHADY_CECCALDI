# TP1 Synthèse Système

## **Introduction**
Ce projet consiste à développer un mini-shell EnseaSh en langage C. Ce shell permet d'exécuter des commandes de base de manière interactive, avec des fonctionnalités telles que la gestion des redirections d'entrée et de sortie, la mesure du temps d'exécution des commandes, et la gestion des erreurs.

Ce document explique les objectifs, les fonctionnalités principales et les parties importantes du code.

---

## OBJECTIFS DU PROJET

- Créer un shell interactif permettant l'exécution de commandes utilisateur comme dans un terminal classique.
- Gérer les redirections d'entrée et de sortie pour manipuler les fichiers.
- Mesurer le temps d'exécution des commandes et afficher les codes de retour des processus enfant.
- Implémenter une structure modulaire avec des fichiers dédiés à des fonctionnalités spécifiques (redirection, gestion des processus, etc.).
- Faciliter la maintenance et la compréhension du code en suivant les bonnes pratiques de programmation.

---

## FONCTIONNALITÉS PRINCIPALES

### 1. Affichage interactif avec un prompt personnalisé
- Le shell affiche un prompt ("enseash %") en attente d'une commande utilisateur.
- Si l'utilisateur ne saisit rien, le prompt est réaffiché.

### 2. Exécution des commandes
- Les commandes saisies sont analysées, et un processus enfant (à l'aide de "fork") est créé pour exécuter la commande via "execvp".
- En cas d'erreur (commande introuvable), un message est affiché.

### 3. Gestion des redirections (écriture et lecture)
- Le fichier question7.c gère les redirections :
  - `>` pour rediriger la sortie standard vers un fichier.
  - `<` pour rediriger l'entrée standard depuis un fichier.
- Les arguments associés aux redirections sont traités et retirés des arguments passés à la commande.

### 4. Mesure du temps d'exécution
- Le fichier "timer.c" calcule le temps d'exécution des commandes en millisecondes en utilisant "clock_gettime".

### 5. Affichage des codes de sortie et des signaux
- Les codes de retour ou signaux d'erreur (éventuellement causés par une interruption) sont affichés.



---

## PARTIES IMPORTANTES DU CODE

### 1. Fichier main.c
- Rôle principal :
  - Gérer la boucle principale du shell.
  - Lire les commandes utilisateur avec "read".
  - Créer des processus enfants via "fork" pour exécuter les commandes.
- Fonctionnalités clés :
  - Gestion des erreurs (ex. fork ou commande introuvable).
  - Intégration des autres modules (redirection, mesure du temps).

### 2. Fichier question7.c : Gestion des redirections
- Implémente la gestion des redirections ">" et "<".
- Utilise "dup2" pour rediriger "stdout" ou "stdin" vers un fichier.
- Gère les erreurs comme l'absence de fichier ou l'échec d'ouverture.
- Cela permet d'écrire les sorties d'une commande dans un fichier ou de lire l'entrée depuis un fichier.

### 3. Fichier timer.c : Calcul du temps d'exécution
- Fonctions importantes :
  - "measure_execution_time" : Calcule le temps d'exécution en millisecondes.
  - "display_exit_code_with_time" : Affiche le code de sortie ou le signal avec le temps d'exécution.


## PROBLEMES RENCONTRES :

- Question 6 : plusieurs commandes ne marchaient pas sur Macos comme "-i" et "osfortune" il a donc fallu trouver des équiavlents pour pouvoir tester notre code comme "-s fortunes" et utiliser "brew install" pour installer les commandes nécessaires.
- Questions 1, 2, 3 : on a eu un problème de linker qui a ipliqué une modification du Makefile. Cela était dû au fait que nous avons fait un fichier différent pour chaque question pour rendre le code plus lisible et compréhensibe. 

## CONCLUSION
Ce projet constitue une introduction solide à la programmation système en C. Il couvre des concepts essentiels tels que la création de processus, la redirection des flux, et l'interaction utilisateur. Chaque module apporte une contribution importante à l'architecture globale, rendant le shell à la fois fonctionnel et extensible.

