#ifndef GRAPHE_H
#define GRAPHE_H
#include "../inc/sommet.h"
int alea(double p);
void genererUnGraphe(int **matrice,int m,int d);
int trouverUnSousGraphe(int** matrice,int cpt,int m,int x,int* visiter,int max,int* final);
struct Arbitre genererUnGrapheConnexe(int** matrice, int m, int* visiter, int* final, int* cpt);
int** getSousGraphe(A arb,int index,int size,int* taille);
int* initGraphe();

#endif