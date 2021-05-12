#ifndef SOMMET_H
#define SOMMET_H

#include <stdio.h>
#include <stdlib.h>

struct sommet
{
    int index;
    double* vecteurStochastique;
    double maxBenefice;
    double minBenefice;
    int cliqueMax;
    int couleur;
};
typedef struct sommet Sommet;

struct arbitre
{
    int** matrice;
    Sommet* listeSommet;
};
typedef struct arbitre Arbitre;

int alea(double p);
void genererUnGraphe(int **matrice,int m,int d);
int trouverUnSousGraphe(int** matrice,int cpt,int m,int x,int* visiter,int max,int* final);
Arbitre genererUnGrapheConnexe(int** matrice,int m,int* visiter,int* final,int* cpt);
int** getSousGraphe(Arbitre arb,int index,int size,int* taille)

#endif