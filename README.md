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

![Description de l'image 1](./image/image1.png)

Ici, dup2 copie fd sur STDOUT_FILENO et de même pour STDIN_FILENO.

![Description de l'image 2](./image/image2.png)

De plus, il était nécessaire de vérifier si l'argument courant était le symbole “<”, indiquant une redirection d’entrée, d’où l’utilisation de la fonction “strcmp” qui compare le contenu de args [i] avec la chaîne “<”. Si c’est le cas, cela signifie qu’un fichier d’entrée doit être spécifié pour rediriger l’entrée standard (stdin) à partir de ce fichier.


Ensuite, nous n’avions pas pensé à la gestion des erreurs comme l'absence de fichier ou l'échec d'ouverture, jusqu'à ce que nous nous rendions compte qu’il était nécessaire pour savoir si notre code marchait. 


Ce code permet donc d'écrire les sorties d'une commande dans un fichier ou de lire l'entrée depuis un fichier.


### 3. Fichier question 5.c : Calcul du temps d'exécution

Ce code mesure et affiche le temps d'exécution d'un processus enfant (ou tâche) et affiche son code de sortie ou signal de terminaison avec un indicateur de temps.

Les fonctions importantes sont :

- "measure_execution_time" : Calcule le temps d'exécution en millisecondes. Elle prend trois arguments en entrée : deux “timespec” (au début et à la fin), et un pointeur “long” pour enregistrer le temps calculé. Son but est de soustraire les secondes et nanosecondes des deux structures pour calculer le temps écoulé, puis le convertir en millisecondes. Elle renvoie en sortie le temps écoulé en millisecondes.
  
![Description de l'image 3](./image/image3.png)

- "display_exit_code_with_time" : Affiche le code de sortie ou le signal avec le temps d'exécution. Elle prend deux arguments en entrées : “status”, qui définit le statut d'attente du processus, utilisé pour déterminer le mode de fin (normal, signal, inconnu), et “exec_time”, qui représente le temps d'exécution en millisecondes. Son but est de déterminer le type de terminaison et générer un message correspondant au code ou signal, avec le temps d'exécution. Affiche ensuite une invite (“enseash %”).

![Description de l'image 4](./image/image4.png)

Nous avons créé ces deux fonctions car pour obtenir le résultat demandé, il était nécessaire d’avoir une collaboration entre ces deux fonctions :  sans "measure_execution_time", il serait impossible de connaître la durée d’exécution de la commande, sans "display_exit_code_with_time", le temps mesuré resterait inutile car il ne serait pas présenté à l’utilisateur avec le contexte approprié (exit code, signal).

![Description de l'image 5](./image/image5.png)

On fait appel à la fonction  clock_gettime dans le main pour mesurer le temps de départ et d’arrivée, puis on crée un processus enfant (pid == 0) pour exécuter une tâche, au profit du père : il prépare et exécute la commande via execvp, gère les erreurs d’exécution en affichant un message d’échec et en se terminant. Le processus parent (pid > 0) attend que l’enfant termine pour poursuivre son exécution, il utilise la valeur de retour de l’enfant pour effectuer des actions ou afficher des messages en fonction de l'état de la commande. 
Ces étapes permettent au programme de gérer proprement l’exécution d’une commande externe et de fournir un retour utilisateur en cas d’erreur.



## PROBLEMES RENCONTRES :

- Question 6 : plusieurs commandes ne marchaient pas sur Macos comme "-i" et "osfortune" il a donc fallu trouver des équivalents pour pouvoir tester notre code comme "-s fortunes" et utiliser "brew install" pour installer les commandes nécessaires. De plus notre code de départ était trop complexe donc cela nous a pris du temps de le simplifier pour arriver au bon résultat et comprendre que l’utilisation de execvp nous permettait aussi de répondre à cette question ( avec v : les arguments sont passés en une fois dans un (char **) dont le dernier élément est (char*)NULL et p : l’executable donné en 1er est recherché dans le PATH)		

- Questions 1, 2, 3 : on a eu un problème de linker qui a impliqué une modification du Makefile. Cela nous a pris beaucoup de temps pour essayer de résoudre ce problème. Cela était dû au fait que nous avons fait un fichier différent pour chaque question pour rendre le code plus lisible et compréhensible.


## CONCLUSION
Ce projet constitue une introduction solide à la programmation système en C. De plus, il nous a permis de plonger profondément dans le cours et comprendre concrètement certains processus et fonctions en nous obligeant à les réutiliser dans ce contexte.  Il couvre des concepts essentiels tels que la création de processus, la redirection des flux, et l'interaction utilisateur. Chaque module apporte une contribution importante à l'architecture globale, rendant le shell à la fois fonctionnel et extensible. De plus, il nous a appris à écrire un code propre et lisible en fractionnant chaque question dans un fichier spécifique et donc à nous confronter à d’autres problèmes et élargir notre culture informatique en trouvant de nouvelles solutions variées.



