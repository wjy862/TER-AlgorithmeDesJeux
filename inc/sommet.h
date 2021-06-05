#ifndef SOMMET_H
#define SOMMET_H
#include "parametre.h"

int calculerSommeConflits();
void calculerNbrColorationPropre(/*int times*/);
double calculerNbrCouleurTotal();
void initVecteurStochastique();
void initSommet(int index,Sommet listeSommet[]);
Arbitre initArbitre(int(*matrice)/*[tailleSommet]*/);
double unif();
int getCouleur(Sommet pSommet);
void colorier();
int isConflit(Sommet unSommet,Sommet autreSommet);
void calculerArret();
void calculerConflit();
int** getSousGrapheClique(Arbitre arb,int index,int size,int* taille);
int diminuer(int* binaire, int taille,int i);
int calculerCliqueMaximale(Arbitre arb,int f);
void calculercliqueMax();
int calculerNbrCouleurLocal(Arbitre arb,int index);
void calculerCouleurSsgraphe();
void calculerCouleurSsgraphe();
int isVoisin(int ligne,int colonne);
int isDefferentFromAnyElements(int index,int *list,int taille);
int findNbrVoisinNonColorie(int index,int *sommetsColorie,int tailleSommetsColorie);
int getProchainVoisinLeMoinsContraint(int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie,int tailleVoisinNonColorie);
void heuristiqueColorier(int index,int *sommetsColorie,int tailleSommetsColorie);
int* trouverListeVoisin(int *sommetsColorie,int tailleSommetsColorie);
int calculerTailleVoisinNonColorie(int *sommetsColorie,int tailleSommetsColorie);
int* calculerVoisinsNonColorie(int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie);
int heuristiqueColoriser(int count,int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie,int tailleVoisinNonColorie);
int initNbrColoration();
int calculerMinColorationPropre();
void calculerNbrCouleursNbrConflitsNbNash();
#endif









































