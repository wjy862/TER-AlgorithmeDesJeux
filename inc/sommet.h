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

double unif();

#endif