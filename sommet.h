#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <time.h>


#define I 6
#define J 5
#define COULEUR 5

struct Sommet{
    int index;
    double vecteurStochastique[COULEUR];
    double maxBenefice;
    double minBenefice;
    int cliqueMax;
    int couleur;
};
typedef struct Sommet *Sommet;

typedef struct Arbitre{
    int (*matrice)[J];
    Sommet listeSommet[J];
}*Arbitre;




double unif() {
    static unsigned int seed = 0;
    seed++;
    srand((unsigned) time(NULL) + seed * seed);
    return (double)random()/((double)RAND_MAX);
}
int getCouleur(Sommet pSommet){
   /* for (int i = 0; i < 1; ++i) {
        for (int y = 0; y < COULEUR; ++y) {
            printf("&pSommet->vecteurStochastique %d): %d\n",  y,
                   (pSommet->vecteurStochastique + y));
            printf("*pSommet->vecteurStochastique %d): %lf\n",  y,
                   *(pSommet->vecteurStochastique + y));
        }
    }*/
    double *p= pSommet->vecteurStochastique;
    double cumuleeP=0.0;
    double thisP=unif();
    printf("thisP: %lf\n", thisP);
    for (int k = 0; k < COULEUR; k++) {
        cumuleeP+=*(p+k);
        printf("P%d: %lf\n",k, cumuleeP);
        if(thisP<cumuleeP) {
            //printf("k: %d\n", k);
            pSommet->couleur=k;
            return k;
        }
    }
    exit(-1);;
}
int getCouleur1(Arbitre pArbitre){
    for (int i = 0; i < 1; ++i) {
        for (int y = 0; y < COULEUR; y++) {
            printf("&(pArbitre->listeSommet[%d]->vecteurStochastique %d): %d\n", i, y,
                   (pArbitre->listeSommet[i]->vecteurStochastique + y));
            printf("*(pArbitre->listeSommet[%d]->vecteurStochastique %d): %lf\n", i, y,
                   *(pArbitre->listeSommet[i]->vecteurStochastique + y));
        }
    }
    double *vs=pArbitre->listeSommet[0]->vecteurStochastique;
    double P0=*vs;
    double P1=*(vs)+1;
    printf("P0: %lf\n", P0);//0.2
    printf("P1: %lf\n", P1);//0.4
    double p=unif();
    if(p<0.2) return 0;

}

void setSommet(int index,Sommet listeSommet[]){
    Sommet pSommet;
    pSommet=malloc(sizeof(struct Sommet));
    if (!pSommet) exit(1);
    printf("beginning of vertex initialisation\n");
    pSommet->index=index;
    pSommet->couleur=-1;
    printf("pSommet->index: %d\n", pSommet->index);//5

    //pSommet->vecteurStochastique=malloc(COULEUR*sizeof(double));
    for (int k = 0; k < COULEUR; k++) {
        pSommet->vecteurStochastique[k]=0.2;
        printf("*vecteurStochastique[%d]: %lf\n", k,*(pSommet->vecteurStochastique+k));
    }
    listeSommet[index]=pSommet;
    printf(" &pSommet->vecteurStochastique[0]: %d\n", (pSommet->vecteurStochastique));
    printf(" *pSommet->vecteurStochastique[0]: %lf\n", *(pSommet->vecteurStochastique));
    printf("vertex initialisation succeed\n\n");
}
Arbitre setArbitre(int matrice[I][J]){
    Arbitre pArbitre;
    //pArbitre=malloc(sizeof(struct Arbitre)+J*sizeof(struct Sommet));
    pArbitre=malloc(sizeof(int)+COULEUR*sizeof(Sommet));
    if (!pArbitre) exit(1);
    pArbitre->matrice=matrice;
    /*printf("%d\n", sizeof(*(pArbitre->matrice)));
    printf("%d\n", **(pArbitre->matrice));//5
    printf("%d\n", **(pArbitre->matrice+1));//0
    printf("%d\n", *(*(pArbitre->matrice)+1));//5
    printf("%d\n", *(*(pArbitre->matrice)+2));//0
    printf("%d\n", &matrice[3][0]);//-445398948
    printf("%d\n", matrice[3][0]);//1*/
    for (int i = 0; i < J; i++) {
        //pArbitre->listeSommet[i]=setSommet(i);
        setSommet(i,pArbitre->listeSommet);
    }
   printf("&(pArbitre %d): %d\n", 0,pArbitre);
    printf("&(pArbitre->listeSommet[%d] %d): %d\n", 0, 0,(pArbitre->listeSommet[0]));
    for (int i = 0; i < J; i++) {
        for (int y = 0; y < COULEUR; y++) {
            printf("&(pArbitre->listeSommet[%d]->vecteurStochastique %d): %d\n", i, y,
                   (pArbitre->listeSommet[i]->vecteurStochastique + y));
            printf("*(pArbitre->listeSommet[%d]->vecteurStochastique %d): %lf\n", i, y,
                   *(pArbitre->listeSommet[i]->vecteurStochastique + y));
        }
    }
    return pArbitre;
}


void Clorier(Arbitre pArbitre){
    for(int a = 0; a < J; ++a){
       //pArbitre->listeSommet[a]->couleur=getCouleur(pArbitre->listeSommet[a]);
        getCouleur(pArbitre->listeSommet[a]);
    }
    //getCouleur(pArbitre->listeSommet[4]);
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




void print(){
    printf("Hello, World!\n");
}