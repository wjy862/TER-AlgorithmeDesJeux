#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <time.h>

/**********************************************************************parametre variable****************************************************************/
#define DEGRE 5//moyenne degré
#define TIMES 10//nb répéter le jeu
#define alpha 0.6 //alpha*beneficeGlobale()
#define belta 0.4//belta*beneficeLocale
#define THETA1 0.01//Learning rate parameter, 0<THETA<1
#define THETA2 0.005//Learning rate parameter, 0<THETA<1
#define N 1e6//itération
#define THETA 0.1//Learning rate parameter, 0<THETA<1
#define THRESHOULD 0.999//Seuil de probabilité à atteindre

int minTailleSommet=3;//minTailleSommet est la minimum nb sommet qu'on peut avoir dans le graphe
int maxTailleSommet=20;//maxTailleSommet est la maximum nb sommet qu'on peut avoir dans le graphe

/*********************************************************structure des données******************************************************************************/
struct Sommet{
    int index;
    int couleur;
    double benefice;
    double maxBenefice;
    double minBenefice;
    int cliqueMax;
    int nbrArrets;
    int nbrConflits;
    int coul_ss_graph;
    double *vecteurStochastique;
};
typedef struct Sommet *Sommet;

struct Arbitre{
    int tailleSommet;
    int tailleArret;
    int *matrice;
    Sommet *listeSommet;
};
typedef struct Arbitre *Arbitre,A;

/*******************************************************************parametres fixés******************************************************************/
Arbitre pArbitre;
int couleurHeuristique;
double nbrCouleur;//Nombre total des couleurs dans la graphe
double nbStrategies;//(double) couleurHeuristique pour calculer
int nbrColorationPropre;
int sommeConflits;
int *matriceRepartitionCouleurConflit;
int tailleSommet;//ne change pas svp, utilise minTailleSommet et maxTailleSommet pour changer nb sommet du graphe
int tailleArret;//ne change pas svp, utilise minTailleSommet et maxTailleSommet pour changer nb sommet du graphe

/*apprandissage.h*/
double r;//Number of actions
int a;//this action
double *p;//Probability vector,[p[0],p[1]...p[r]]
double utilite;//Environmental response (P,Q,S)-> utilité

int isVoisin(int ligne,int colonne);
int calculerSommeConflits();
int calculerMinColorationPropre();
/*free les mémoires*/
void freeAll();