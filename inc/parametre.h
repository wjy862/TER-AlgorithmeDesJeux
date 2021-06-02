#ifndef PARAMETRE_H
#define PARAMETRE_H

#include "struct.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <time.h>
/**********************************************************************parametre variable****************************************************************/
//#define DEGRE 5//moyenne degré
#define TIMES 10//nb répéter le jeu
#define N 1e6//itération
#define alpha 0.6 //alpha*beneficeGlobale()
#define belta 0.4//belta*beneficeLocale
#define THETA1 0.01//Learning rate parameter, 0<THETA<1
#define THETA2 0.005//Learning rate parameter, 0<THETA<1
#define THRESHOULD 0.999//Seuil de probabilité à atteindre

#define METHODE linearRewardInaction
//#define METHODE linearRewardPenalty;
//#define METHODE linearRewardPenalty2

#define GRAPHE matrice
//#define GRAPHE graphe1
//#define GRAPHE graphe2
//#define GRAPHE graphe3
//#define GRAPHE graphe4
//#define GRAPHE graphe5
//#define GRAPHE graphe6

#define maxTailleSommet 20//maxTailleSommet est la maximum nb sommet qu'on peut avoir dans le graphe
extern int minTailleSommet;//=6;//minTailleSommet est la minimum nb sommet qu'on peut avoir dans le graphe
extern int minDegre;//=6;
extern int maxDegre;//=6;


/*********************************************************structure des données******************************************************************************/
// struct Sommet{
//     int index;
//     int couleur;
//     double benefice;
//     double maxBenefice;
//     double minBenefice;
//     int cliqueMax;
//     int nbrArrets;
//     int nbrConflits;
//     int coul_ss_graph;
//     double *vecteurStochastique;
// };
// typedef struct Sommet *Sommet;

// struct Arbitre{
//     int tailleSommet;
//     int tailleArret;
//     int *matrice;
//     Sommet *listeSommet;
// };
// typedef struct Arbitre *Arbitre,A;

/*******************************************************************parametres fixés******************************************************************/
extern Arbitre pArbitre;
extern int couleurHeuristique;
extern double nbrCouleur;//Nombre total des couleurs dans la graphe
extern double nbStrategies;//(double) couleurHeuristique pour calculer
extern int nbrColorationPropre;
extern int sommeConflits;
extern int *matriceRepartitionCouleurConflit;
extern int tailleSommet;//ne change pas svp, utilise minTailleSommet et maxTailleSommet pour changer nb sommet du graphe
extern int tailleArret;//ne change pas svp, utilise minTailleSommet et maxTailleSommet pour changer nb sommet du graphe

/*apprandissage.h*/
extern double r;//Number of actions
extern int a;//this action
extern double *p;//Probability vector,[p[0],p[1]...p[r]]
extern double utilite;//Environmental response (P,Q,S)-> utilité


/*graphe1 est graphe biparti de taille 6
Lors d'attaindre l'équilibre de nash 1000 fois
(nb couleurs: 2, nb conflits: 0) apparait 997 fois
(nb couleurs: 2, nb conflits: 3) apparait 3 fois
Nombre de couleur total: 2
Graphe de 6 sommets, nbColorationPropre obtenue est de 997 avec minCouleurs de 2, tauxColorationPropre est de 0.997000
 * */
extern int graphe1[maxTailleSommet][maxTailleSommet];
extern int graphe2[maxTailleSommet][maxTailleSommet];
extern int graphe3[maxTailleSommet][maxTailleSommet];
extern int graphe4[maxTailleSommet][maxTailleSommet];
extern int graphe5[maxTailleSommet][maxTailleSommet];
extern int graphe6[maxTailleSommet][maxTailleSommet];

// extern int graphe1[maxTailleSommet][maxTailleSommet]=
//         {0,1,0,1,0,1,
//          1,0,1,0,1,0,
//          0,1,0,1,0,1,
//          1,0,1,0,1,0,
//          0,1,0,1,0,1,
//          1,0,1,0,1,0};
/*graphe2 n'est pas un graphe biparti, Coloration minimum=3
Lors d'attaindre l'équilibre de nash 1000 fois
(nb couleurs: 2, nb conflits: 1) apparait 143 fois
(nb couleurs: 3, nb conflits: 0) apparait 852 fois
(nb couleurs: 3, nb conflits: 1) apparait 5 fois
Nombre de couleur total: 3
Graphe de 7 sommets, nbColorationPropre obtenue est de 852 avec minCouleurs de 3, tauxColorationPropre est de 0.852000
 * */
// extern int graphe2[maxTailleSommet][maxTailleSommet]=
//         {0,1,0,1,0,1,0,
//          1,0,1,0,1,0,0,
//          0,1,0,1,0,1,0,
//          1,0,1,0,1,0,0,
//          0,1,0,1,0,1,1,
//          1,0,1,0,1,0,1,
//          0,0,0,0,1,1,0};
/*graphe3 est graphe biparti de taille 10
Lors d'attaindre l'équilibre de nash 1000 fois
(nb couleurs: 2, nb conflits: 0) apparait 941 fois
(nb couleurs: 2, nb conflits: 2) apparait 28 fois
(nb couleurs: 2, nb conflits: 3) apparait 6 fois
(nb couleurs: 2, nb conflits: 4) apparait 25 fois
Nombre de couleur total: 2
Graphe de 10 sommets, nbColorationPropre obtenue est de 941 avec minCouleurs de 2, tauxColorationPropre est de 0.941000
 * */
// extern int graphe3[maxTailleSommet][maxTailleSommet]=
//         {0,0,0,1,0,1,0,0,0,0,
//          0,0,1,0,1,0,0,0,0,0,
//          0,1,0,0,0,1,0,1,0,0,
//          1,0,0,0,1,0,0,0,0,0,
//          0,1,0,1,0,0,0,1,0,1,
//          1,0,1,0,0,0,1,0,1,0,
//          0,0,0,0,0,1,0,0,0,1,
//          0,0,1,0,1,0,0,0,1,0,
//          0,0,0,0,0,1,0,1,0,1,
//          0,0,0,0,1,0,1,0,1,0};
/*graphe4 est un graphe biparti, son taille 20

fonction Benefice sousgraphe couleur
Lors d'attaindre l'équilibre de nash 1000 fois
(nb couleurs: 2, nb conflits: 0) apparait 477 fois
(nb couleurs: 2, nb conflits: 1) apparait 361 fois
(nb couleurs: 2, nb conflits: 2) apparait 81 fois
(nb couleurs: 2, nb conflits: 3) apparait 19 fois
(nb couleurs: 2, nb conflits: 4) apparait 48 fois
(nb couleurs: 2, nb conflits: 5) apparait 9 fois
(nb couleurs: 2, nb conflits: 6) apparait 4 fois
(nb couleurs: 2, nb conflits: 7) apparait 1 fois
Nombre de couleur total: 2
Graphe de 20 sommets, nbColorationPropre obtenue est de 477 avec minCouleurs de 2, tauxColorationPropre est de 0.477000

fonction Benefice le plus simple
Lors d'attaindre l'équilibre de nash 1000 fois
(nb couleurs: 2, nb conflits: 0) apparait 458 fois
(nb couleurs: 2, nb conflits: 1) apparait 382 fois
(nb couleurs: 2, nb conflits: 2) apparait 72 fois
(nb couleurs: 2, nb conflits: 3) apparait 27 fois
(nb couleurs: 2, nb conflits: 4) apparait 44 fois
(nb couleurs: 2, nb conflits: 5) apparait 14 fois
(nb couleurs: 2, nb conflits: 6) apparait 2 fois
(nb couleurs: 2, nb conflits: 8) apparait 1 fois
Nombre de couleur total: 2
Graphe de 20 sommets, nbColorationPropre obtenue est de 458 avec minCouleurs de 2, tauxColorationPropre est de 0.458000

fonction Benefice nbr de couleur
Lors d'attaindre l'équilibre de nash 1000 fois
(nb couleurs: 2, nb conflits: 0) apparait 504 fois
(nb couleurs: 2, nb conflits: 1) apparait 341 fois
(nb couleurs: 2, nb conflits: 2) apparait 58 fois
(nb couleurs: 2, nb conflits: 3) apparait 28 fois
(nb couleurs: 2, nb conflits: 4) apparait 51 fois
(nb couleurs: 2, nb conflits: 5) apparait 12 fois
(nb couleurs: 2, nb conflits: 6) apparait 5 fois
(nb couleurs: 2, nb conflits: 8) apparait 1 fois
Nombre de couleur total: 2
Graphe de 20 sommets, nbColorationPropre obtenue est de 504 avec minCouleurs de 2, tauxColorationPropre est de 0.504000
 Lors d'attaindre l'équilibre de nash 1000 fois
(nb couleurs: 2, nb conflits: 0) apparait 475 fois
(nb couleurs: 2, nb conflits: 1) apparait 377 fois
(nb couleurs: 2, nb conflits: 2) apparait 83 fois
(nb couleurs: 2, nb conflits: 3) apparait 15 fois
(nb couleurs: 2, nb conflits: 4) apparait 38 fois
(nb couleurs: 2, nb conflits: 5) apparait 8 fois
(nb couleurs: 2, nb conflits: 6) apparait 3 fois
(nb couleurs: 2, nb conflits: 7) apparait 1 fois
Nombre de couleur total: 2
Graphe de 20 sommets, nbColorationPropre obtenue est de 475 avec minCouleurs de 2, tauxColorationPropre est de 0.475000

 fonction Benefice nbr de couleur
 linearRewardPenalty
 Lors d'attaindre l'équilibre de nash 10 fois
(nb couleurs: 2, nb conflits: 11) apparait 1 fois
(nb couleurs: 2, nb conflits: 13) apparait 2 fois
(nb couleurs: 2, nb conflits: 14) apparait 2 fois
(nb couleurs: 2, nb conflits: 15) apparait 1 fois
(nb couleurs: 2, nb conflits: 16) apparait 1 fois
(nb couleurs: 2, nb conflits: 18) apparait 1 fois
(nb couleurs: 2, nb conflits: 19) apparait 2 fois
Nombre de couleur total: 2
Graphe de 20 sommets, nbColorationPropre obtenue est de 0 avec minCouleurs de 2147483647, tauxColorationPropre est de 0.000000
Process finished with exit code 0

 fonction Benefice nbr de couleur
 linearRewardPenalty2
 0.05 0.025
 Lors d'attaindre l'équilibre de nash 10 fois
(nb couleurs: 2, nb conflits: 0) apparait 5 fois
(nb couleurs: 2, nb conflits: 1) apparait 3 fois
(nb couleurs: 2, nb conflits: 2) apparait 2 fois
Nombre de couleur total: 2
Graphe de 20 sommets, nbColorationPropre obtenue est de 5 avec minCouleurs de 2, tauxColorationPropre est de 0.500000
 * */
// extern int graphe4[maxTailleSommet][maxTailleSommet]=
//         {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//          0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
//          0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
//          1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//          0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,
//          1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
//          0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
//          0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
//          0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,
//          0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
//          0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,
//          0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,
//          0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,
//          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
//          0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,
//          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,
//          0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0};
/*graphe5 n'est pas un graphe biparti, son taille 20
Lors d'attaindre l'équilibre de nash 10 fois
(nb couleurs: 3, nb conflits: 0) apparait 9 fois
(nb couleurs: 3, nb conflits: 1) apparait 1 fois
Nombre de couleur total: 3
 * */
// extern int graphe5[maxTailleSommet][maxTailleSommet]=
//         {0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
//          0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
//          0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
//          1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//          0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,
//          1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
//          0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
//          0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
//          0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,
//          0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
//          1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,
//          0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,
//          0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,
//          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
//          0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,
//          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,
//          0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0};
/*graphe6 est graphe planaire de taille 6
Lors d'attaindre l'équilibre de nash 1000 fois
(nb couleurs: 2, nb conflits: 2) apparait 37 fois
(nb couleurs: 3, nb conflits: 0) apparait 726 fois
(nb couleurs: 3, nb conflits: 1) apparait 71 fois
(nb couleurs: 3, nb conflits: 2) apparait 2 fois
(nb couleurs: 4, nb conflits: 0) apparait 164 fois
Nombre de couleur total: 4
Graphe de 6 sommets, nbColorationPropre obtenue est de 890 avec minCouleurs de 3, tauxColorationPropre est de 0.890000
 * */
// extern int graphe6[maxTailleSommet][maxTailleSommet]=
//         {0,1,1,1,0,1,
//          1,0,0,1,0,1,
//          1,0,0,1,1,0,
//          1,1,1,0,1,0,
//          0,0,1,1,0,1,
//          1,1,0,0,1,0};

int isVoisin(int ligne,int colonne);
int calculerSommeConflits();
int calculerMinColorationPropre();
/*free les mémoires*/
void freeAll();
void resetArbitre();

#endif