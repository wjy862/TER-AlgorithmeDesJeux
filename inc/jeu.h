#ifndef JEU_H
#define JEU_H
#include "parametre.h"

void initMatriceRepartitionCouleurConflit();
int* initParametres(int nbrSommet,int minDegre);
int run();
void commenceColoration();
void commenceDuJeu(int *matrice, int count);
void freeAll();
void  resetSommet(Sommet pSommet);
void resetArbitre();
#endif
