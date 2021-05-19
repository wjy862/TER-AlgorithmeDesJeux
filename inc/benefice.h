#ifndef BENEFICE_H
#define BENEFICE_H
#include "../inc/sommet.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define alpha 0.6
#define belta 0.5

double beneficeLocale(Sommet pSommet);
double beneficeGlobale();
double fonctionBenefice(Sommet pSommet);
void updateBenefice(Sommet pSommet);
void calculerBenefice();
#endif