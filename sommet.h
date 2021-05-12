#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <time.h>


#define I 5
#define J 5
#define COULEUR 5

struct Sommet{
    int index;
    double vecteurStochastique[COULEUR];
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
    int (*matrice)[J];
    Sommet listeSommet[J];
}*Arbitre;


double unif() {
    static unsigned int seed = 0;
    seed++;
    srand((unsigned) time(NULL) + seed * seed);
    return (double)random()/((double)RAND_MAX);
}
void printMatice(int tailleSommet,int tailleArret,int (*matrice)[J]){
    printf("tailleSommet: %d\n", tailleSommet);//5
    printf("tailleArret: %d\n", tailleArret);//5
    for (int k = 0; k < I; k++) {
        for (int m = 0; m < J; m++) {
            printf("%d ", *(*(matrice+k)+m));//5
        }
        printf("\n");
    }
    /*printf("%d\n", sizeof(*(pArbitre->matrice)));
    printf("%d\n", **(pArbitre->matrice));//5
    printf("%d\n", **(pArbitre->matrice+1));//0
    printf("%d\n", *(*(pArbitre->matrice)+1));//5
    printf("%d\n", *(*(pArbitre->matrice)+2));//0
    printf("%d\n", &matrice[3][0]);//-445398948
    printf("%d\n", matrice[3][0]);//1*/
}
printVecteurStochastique(int i,int y,double vecteurStochastique[COULEUR]){
    printf("&(pArbitre->listeSommet[%d]->vecteurStochastique %d): %d\n", i, y,
           (vecteurStochastique + y));
    printf("*(pArbitre->listeSommet[%d]->vecteurStochastique %d): %lf\n", i, y,
           *(vecteurStochastique + y));
}
void printSommet(Sommet pSommet){
    printf("pSommet->index: %d\n", pSommet->index);
    printf("pSommet->couleur: %d\n", pSommet->couleur);
    printf("pSommet->nbrConflits: %d\n", pSommet->nbrConflits);
    printf("pSommet->benefice: %d\n", pSommet->benefice);
    printf("pSommet->maxBenefice: %d\n", pSommet->maxBenefice);
    printf("pSommet->minBenefice: %d\n", pSommet->minBenefice);
    printf("pSommet->cliqueMax: %d\n", pSommet->cliqueMax);
    for (int k = 0; k < COULEUR; k++) {
        pSommet->vecteurStochastique[k]=0.2;
        printf("*vecteurStochastique[%d]: %lf\n", k,*(pSommet->vecteurStochastique+k));
    }
}
void printArbitre(Arbitre pArbitre){
    printf("\nBeginning of printArbitre\n");
    printf("Sizeof(pArbitre)%ld\n", sizeof(pArbitre));//8
    printf("&(pArbitre %d): %d\n", 0,pArbitre);
    printf("&(pArbitre->listeSommet[%d] %d): %d\n", 0, 0,(pArbitre->listeSommet[0]));
    printMatice(pArbitre->tailleSommet,pArbitre->tailleArret,pArbitre->matrice);
    for (int i = 0; i < J; i++) {
        printSommet(pArbitre->listeSommet[i]);
    }
    printf("end of printArbitre\n");
}


int getCouleur(Sommet pSommet){
    /*la probalibité pour une stratégie*/
    double *p= pSommet->vecteurStochastique;
    /*la probalilité cumulée*/
    double cumuleeP=0.0;
    double thisP=unif();
    printf("Génerer un p suite de la loi uniforme, thisP: %lf\n", thisP);
    for (int k = 0; k < COULEUR; k++) {
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

void setSommet(int index,Sommet listeSommet[]){
    Sommet pSommet;
    pSommet=malloc(sizeof(struct Sommet));
    if (!pSommet) exit(1);
    printf("beginning of vertex%d initialisation\n",index);
    pSommet->index=index;
    pSommet->couleur=-1;
    pSommet->nbrConflits=-1;
    pSommet->benefice=-1;
    pSommet->maxBenefice=0;
    pSommet->minBenefice=0;
    pSommet->cliqueMax=-1;
    for (int k = 0; k < COULEUR; k++) {
        pSommet->vecteurStochastique[k]=0.2;
    }
    listeSommet[index]=pSommet;
    printSommet(pSommet);
    printf("vertex initialisation succeed\n\n");
}
Arbitre setArbitre(int tailleSommet,int tailleArret,int matrice[I][J]){
    printf("beginning of Arbitre initialisation\n");
    Arbitre pArbitre;
    pArbitre=malloc(sizeof(int)+COULEUR*sizeof(Sommet));
    if (!pArbitre) exit(1);
    pArbitre->tailleSommet=tailleSommet;
    pArbitre->tailleArret=tailleArret;
    pArbitre->matrice=matrice;
    //printMatice(pArbitre->matrice);
    for (int i = 0; i < J; i++) {
        setSommet(i,pArbitre->listeSommet);
    }
    printf("Arbitre initialisation succeed\n\n");
    return pArbitre;
}


void Clorier(Arbitre pArbitre){
    for(int a = 0; a < J; a++){
        getCouleur(pArbitre->listeSommet[a]);
    }
}
int isConflit(Sommet unSommet,Sommet autreSommet){
    if(unSommet->couleur==autreSommet->couleur) return 1;
    return 0;
}
void calculerConflit(Arbitre pArbitre){
    for(int b= 0; b< I; b++){
        int count=0;
        for(int c= 0; c< J; c++){
            if(pArbitre->matrice[b][c]==1) count+=isConflit(pArbitre->listeSommet[b],pArbitre->listeSommet[c]);
        }
        pArbitre->listeSommet[b]->nbrConflits=count;
    }
}













































void printMatrice(int matrice[I][J]){
    printf("%d\n", matrice[0][0]);
}

void testPointer(int matrice[I][J]){
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

void testPointer1(int matrice[I][J]){
    int (**p);
    p=matrice;
    myputs(p);
}
