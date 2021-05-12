#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <time.h>


#define TSOMMET 5
#define TARRET 5

int couleur;

struct Sommet{
    int index;
    double *vecteurStochastique;
    double benefice;
    double maxBenefice;
    double minBenefice;
    int cliqueMax;
    int couleur;
    int nbrConflits;
};
typedef struct Sommet *Sommet;

typedef struct Arbitre{
    int tailleSommet;
    int tailleArret;
    int *matrice;
    Sommet *listeSommet;
}*Arbitre;



//print
void printMatice(int tailleSommet,int tailleArret,int *matrice){

    printf("tailleSommet: %d\n", tailleSommet);

    printf("tailleArret: %d\n", tailleArret);
    for (int k = 0; k < tailleSommet; k++) {

        for (int m = 0; m < tailleArret; m++) {

            //printf("%d ", *(*(matrice+k)+m));
            printf("%d ", *(matrice+k*tailleArret+m));
        }
        printf("\n");
    }
}
void printAdresseEtValueVecteurStochastique(int i,int y,double *vecteurStochastique){
    printf("&(pArbitre->listeSommet[%d]->vecteurStochastique %d): %d\n", i, y,
           (vecteurStochastique + y));
    printf("*(pArbitre->listeSommet[%d]->vecteurStochastique %d): %lf\n", i, y,
           *(vecteurStochastique + y));
}
void printSommet(Sommet pSommet){
    printf("pSommet->index: %d\n", pSommet->index);
    printf("pSommet->couleur: %d\n", pSommet->couleur);
    printf("pSommet->nbrConflits: %d\n", pSommet->nbrConflits);
    printf("pSommet->benefice: %lf\n", pSommet->benefice);
    printf("pSommet->maxBenefice: %lf\n", pSommet->maxBenefice);
    printf("pSommet->minBenefice: %lf\n", pSommet->minBenefice);
    printf("pSommet->cliqueMax: %d\n", pSommet->cliqueMax);
    for (int k = 0; k < couleur; k++) {
        printf("*vecteurStochastique[%d]: %lf\n", k,*(pSommet->vecteurStochastique+k));
    }
}
void printArbitre(Arbitre pArbitre){

    printf("\nBeginning of printArbitre\n");
    printf("Sizeof(pArbitre): %ld\n", sizeof(pArbitre));//8
    printf("&(pArbitre %d): %d\n", 0,pArbitre);
    printf("&(pArbitre->listeSommet[%d] %d): %d\n", 0, 0,(pArbitre->listeSommet[0]));
    printMatice(pArbitre->tailleSommet,pArbitre->tailleArret,pArbitre->matrice);
    for (int i = 0; i < pArbitre->tailleSommet; i++) {
        printSommet(pArbitre->listeSommet[i]);
    }
    printf("end of printArbitre\n");
}
//heuristiqueColoration
int heuristiqueColoration(int tailleArret,int *(matrice)[tailleArret]){
    return 3;
}

//initialisation
void setSommet(int index,Sommet listeSommet[]){
    Sommet pSommet;
    pSommet=malloc(sizeof(struct Sommet));
    if (!pSommet) exit(1);
    printf("beginning of vertex%d initialisation\n",index);
    pSommet->index=index;
    pSommet->couleur=-1;
    pSommet->nbrConflits=-1;
    pSommet->benefice=0.0;
    pSommet->maxBenefice=0.0;
    pSommet->minBenefice=0.0;
    pSommet->cliqueMax=-1;
    pSommet->vecteurStochastique= malloc(couleur* sizeof(double));
    for (int k = 0; k < couleur; k++) {
        pSommet->vecteurStochastique[k]=(1.0/couleur);
    }
    listeSommet[index]=pSommet;
    printSommet(pSommet);
    printf("vertex initialisation succeed\n\n");
}
Arbitre setArbitre(int tailleSommet,int tailleArret,int (*matrice)[tailleArret]){
    printf("beginning of Arbitre initialisation\n");
    Arbitre pArbitre;
    pArbitre=malloc(sizeof(int)+couleur*sizeof(Sommet));
    if (!pArbitre) exit(1);
    pArbitre->tailleSommet=tailleSommet;
    pArbitre->tailleArret=tailleArret;
    pArbitre->matrice=matrice[0];
    pArbitre->listeSommet=malloc(tailleSommet*sizeof(Sommet));
    for (int i = 0; i < pArbitre->tailleSommet; i++) {
        setSommet(i,pArbitre->listeSommet);
    }
    printf("Arbitre initialisation succeed\n\n");
    return pArbitre;
}
//colorier
double unif() {
    static unsigned int seed = 0;
    seed++;
    srand((unsigned) time(NULL) + seed * seed);
    return (double)random()/((double)RAND_MAX);
}
int getCouleur(Sommet pSommet){
    /*la probalibité pour une stratégie*/
    double *p= pSommet->vecteurStochastique;
    /*la probalilité cumulée*/
    double cumuleeP=0.0;
    double thisP=unif();
    printf("Génerer un p suite de la loi uniforme, thisP: %lf\n", thisP);
    for (int k = 0; k < couleur; k++) {
        cumuleeP+=*(p+k);
        //printf("P%d: %lf\n",k, cumuleeP);
        if(thisP<cumuleeP) {
            //printf("k: %d\n", k);
            pSommet->couleur=k;
            return k;
        }
    }
    exit(-1);;
}
void Clorier(Arbitre pArbitre){
    printf("beginning of colorier\n");
    for(int a = 0; a < pArbitre->tailleSommet; a++){
        getCouleur(pArbitre->listeSommet[a]);
    }
    printf("beginning of Arbitre colorier\n");
}
//conflit
int isConflit(Sommet unSommet,Sommet autreSommet){
    if(unSommet->couleur==autreSommet->couleur) return 1;
    return 0;
}
void calculerConflit(Arbitre pArbitre){
    printf("beginning of calculerConflit\n");
    for(int b= 0; b<pArbitre->tailleSommet; b++){
        int count=0;
        for(int c= 0; c< pArbitre->tailleArret; c++){
            if(*(pArbitre->matrice+b*pArbitre->tailleArret+c)==1) count+=isConflit(pArbitre->listeSommet[b],pArbitre->listeSommet[c]);
        }
        pArbitre->listeSommet[b]->nbrConflits=count;
    }
    printf("end of calculerConflit\n");
}












































/*
void printMatrice(int (*matrice)[TARRET]){
    printf("%d\n", matrice[0][0]);
}

void testPointer(int (*matrice)[TARRET]){
    int (*p)[5];
    p=matrice;
    printf("%ld\n", sizeof(*(p+1)));
    printf("%d\n", **(p));//5
    printf("%d\n", **(p+1));//0
    printf("%d\n", **((p+1)+1));//0
    printf("%d\n", **(p+3));//1
}
void myputs(int p[6][5]){
    printf("%ld\n", sizeof(*p));//20
    printf("%ld\n", sizeof(**p));//4
    printf("%d\n", **(p));//5
    printf("%d\n", **(p+1));//0
    printf("%d\n", **((p+1)+1));//0
    printf("%d\n", **(p+3));//1
}

void testPointerArray(){
    double a[4] = {1.0, 2.0, 3.0, 4.0};
    double *p = a;
    for (int i = 0; i < 4; i++) {
        printf("a[%d] = %lf \n", i, *(p+i));
        }
}
void testPointerArray1(){
    int a[4] = {1, 2, 3, 4};
    int i;
    for (i = 0; i < 4; i++) {
      printf("a[%d] = %d \n", i, a[i]);
    }
}

void testPointer1(int (*matrice)[TARRET]){
    int (**p);
    p=matrice;
    myputs(p);
}
*/