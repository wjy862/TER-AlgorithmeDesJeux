#ifndef SOMMET_H
#define SOMMET_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DEGRE 5
//#define FPRINTSOMMET 5

extern int tailleSommet;
extern int tailleArret;

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

extern Arbitre pArbitre;//tout ca dans le main
extern int couleurHeuristique;
extern double nbrCouleur;//Nombre total des couleurs dans la graphe
extern double nbStrategies;//(double) couleurHeuristique pour calculer

void printMatice(int thisTailleSommet,int thisTailleArret,int *thisMatrice);
void printIndex(Sommet pSommet);
void printCouleur(Sommet pSommet);
void printBenefice(Sommet pSommet);
void printMaxBenefice(Sommet pSommet);
void printMinBenefice(Sommet pSommet);
void printCliqueMax(Sommet pSommet);
void printNbrArrets(Sommet pSommet);
void printNbrConflits(Sommet pSommet);
void printVecteurStochastique(Sommet pSommet);
void printCouleurSousgraphe(Sommet pSommet);
void printSommet(Sommet pSommet);
void printArbitre();
double calculerNbrCouleurTotal();
void initVecteurStochastique();
void initSommet(int index,Sommet listeSommet[]);
Arbitre initArbitre(int (*matrice)/*[tailleSommet]*/);
double unif();
int getCouleur(Sommet pSommet);
void colorier();
int isConflit(Sommet unSommet,Sommet autreSommet);
void calculerArret();
void calculerConflit();
int isVoisin(int ligne,int colonne);
int** getSousGrapheClique(Arbitre arb,int index,int size,int* taille);
int diminuer(int* binaire, int taille,int i);
int calculerCliqueMaximale(Arbitre arb,int f);
void calculercliqueMax();
int calculerNbrCouleurLocal(Arbitre arb,int index);
void calculerCouleurSsgraphe();
void printSommetsColorie(int *sommetsColorie,int tailleSommetsColorie);
void printTailleSommetsColorie(int tailleSommetsColorie);
void printVoisinsNonColorie(int *voisinsNonColorie,int tailleVoisinNonColorie);
void printTailleVoisinNonColorie(int tailleVoisinNonColorie);
int isDefferentFromAnyElements(int index,int *list,int taille);
int findNbrVoisinNonColorie(int index,int *sommetsColorie,int tailleSommetsColorie);
int getProchainVoisinLeMoinsContraint(int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie,int tailleVoisinNonColorie);
void heuristiqueColorier(int index,int *sommetsColorie,int tailleSommetsColorie);
int* trouverListeVoisin(int *sommetsColorie,int tailleSommetsColorie);
int calculerTailleVoisinNonColorie(int *sommetsColorie,int tailleSommetsColorie);
int* calculerVoisinsNonColorie(int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie);
int heuristiqueColoriser(int count,int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie,int tailleVoisinNonColorie);
int initNbrColoration();
#endif













