//#define THETA 0.1//Learning rate parameter, 0<THETA<1
#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H
#include "parametre.h"

double calculerUtilite(Sommet pSommet);
int isthreshould(Sommet pSommet);
void init(Sommet pSommet);
int linearRewardInaction(Sommet pSommet);
int linearRewardPenalty(Sommet pSommet);
int linearRewardPenalty2(Sommet pSommet);
int apprendissage(Sommet pSommet);
int updateVecteurStochastique();
#endif