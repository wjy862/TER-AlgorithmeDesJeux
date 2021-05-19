#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H
#include "../inc/sommet.h"


#define N 10000//itération
#define THETA 0.1//Learning rate parameter, 0<THETA<1
#define THRESHOULD 0.999//Seuil de probabilité à atteindre

void printR(double r);
void printA(double a);
void printP(double p);
void printUtilite(double utilite);
void printProbabilite(Sommet pSommet,int index);
double calculerUtilite(Sommet pSommet);
int isthreshould(Sommet pSommet);
void init(Sommet pSommet);
int linearRewardInaction(Sommet pSommet);
int linearRewardPenalty(Sommet pSommet);
int apprendissage(Sommet pSommet);
int updateVecteurStochastique();
#endif