#ifndef STRUCT_H
#define STRUCT_H

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


#endif