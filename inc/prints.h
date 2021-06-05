#ifndef PRINTS_H
#define PRINTS_H
#include "parametre.h"

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
void printSommetsColorie(int *sommetsColorie,int tailleSommetsColorie);
void printTailleSommetsColorie(int tailleSommetsColorie);
void printVoisinsNonColorie(int *voisinsNonColorie,int tailleVoisinNonColorie);
void printTailleVoisinNonColorie(int tailleVoisinNonColorie);
void printNbrCouleursEtNbrConflits();
void printNbrColorationPropre(int nbrSommet,double pourcentage);
void printNash();
/*apprendissage.h*/
void printR(double r);
void printA(double a);
void printP(double p);
void printUtilite(double utilite);
void printProbabilite(Sommet pSommet,int index);
#endif
