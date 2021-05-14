#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <time.h>

#define TSOMMET 5
#define TARRET 5

struct Sommet{
    int index;
    int couleur;
    double benefice;
    double maxBenefice;
    double minBenefice;
    int cliqueMax;
    int nbrArrets;
    int nbrConflits;
    double *vecteurStochastique;
};
typedef struct Sommet *Sommet;

typedef struct Arbitre{
    int tailleSommet;
    int tailleArret;
    int *matrice;
    Sommet *listeSommet;
};
typedef struct Arbitre *Arbitre;

Arbitre pArbitre;
int couleurHeuristique;
double nbrCouleur;//Nombre total des couleurs dans la graphe
double nbStrategies;//(double) couleurHeuristique pour calculer
int tailleSommet=5;
int tailleArret=5;
int matrice[TSOMMET][TARRET]={
        {0,1,1,0,0},
        {1,0,1,0,1},
        {1,1,0,1,0},
        {0,0,1,0,1},
        {0,1,0,1,0}
};

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
void printIndex(Sommet pSommet){
    printf("this index : %d\n", pSommet->index);
}
void printCouleur(Sommet pSommet){
    printf("this couleur: %d\n", pSommet->couleur);
}
void printBenefice(Sommet pSommet){
    printf("this benefice: %lf\n", pSommet->benefice);
}
void printMaxBenefice(Sommet pSommet){
    printf("this maxBenefice: %lf\n", pSommet->maxBenefice);
}
void printMinBenefice(Sommet pSommet){
    printf("this minBenefice: %lf\n", pSommet->minBenefice);
}
void printCliqueMax(Sommet pSommet){
    printf("this cliqueMax: %d\n", pSommet->cliqueMax);
}
void printNbrArrets(Sommet pSommet){
    printf("this nbrArrets: %d\n", pSommet->nbrArrets);
}
void printNbrConflits(Sommet pSommet){
    printf("this nbrConflits: %d\n", pSommet->nbrConflits);
}
void printVecteurStochastique(Sommet pSommet){
    for (int k = 0; k < couleurHeuristique; k++) {
        printf("the %dst value of vecteurStochastique: %lf\n", k,*(pSommet->vecteurStochastique+k));
    }
}
void printSommet(Sommet pSommet){
    printIndex(pSommet);
    printCouleur(pSommet);
    printBenefice(pSommet);
    printMaxBenefice(pSommet);
    printMinBenefice(pSommet);
    printCliqueMax(pSommet);
    printNbrArrets(pSommet);
    printNbrConflits(pSommet);
    printVecteurStochastique(pSommet);
}
void printArbitre(){
    printf("\nBeginning of printArbitre\n");
    printf("Size of Arbitre: %ld\n", sizeof(pArbitre));//8
    printf("Adresse of Arbitre : %d\n",pArbitre);
    printf("Adresse of listeSommet: %d\n",(pArbitre->listeSommet[0]));
    printMatice(pArbitre->tailleSommet,pArbitre->tailleArret,pArbitre->matrice);
    for (int i = 0; i < pArbitre->tailleSommet; i++) {
        printSommet(pArbitre->listeSommet[i]);
    }
    printf("End of printArbitre\n\n");
}

double calculerNbrCouleurTotal(){
    int *listCouleurs=malloc(couleurHeuristique*sizeof(int));//chaque index présente une couleur
    int count=0;
    for (int k = 0; k < couleurHeuristique; k++) {
        listCouleurs[k]=0;//initialiser
    }
    for (int i = 0; i < tailleSommet; i++) {
        listCouleurs[pArbitre->listeSommet[i]->couleur]++;//Si un sommet est coloriée par couleur 0 -> listCouleurs[0]++
    }
    for (int j = 0; j < couleurHeuristique; j++) {
        if(listCouleurs[j]!=0) count++;//counter ce qui n'est pas 0 dans la list Couleurs
    }
    free(listCouleurs);
    nbrCouleur=(double)count;
    printf("Nombre total des couleurs dans la graphe: %lf\n",nbrCouleur);
    return nbrCouleur;
}
//heuristiqueColoration
int heuristiqueColoration(){
    int couleurmax=0;


    couleurHeuristique=3;
    return couleurHeuristique;//(int)calculerNbrCouleurTotal()
}

//initialisation
void setSommet(int index,Sommet listeSommet[]){
    Sommet pSommet;
    pSommet=malloc(sizeof(struct Sommet));
    if (!pSommet) exit(1);
    printf("\nBeginning of vertex%d initialisation\n",index);
    pSommet->index=index;
    pSommet->couleur=-1;
    pSommet->nbrConflits=-1;
    pSommet->benefice=0.0;
    pSommet->maxBenefice=0.0;
    pSommet->minBenefice=0.0;
    pSommet->cliqueMax=-1;
    pSommet->nbrArrets=-1;
    pSommet->vecteurStochastique= malloc(couleurHeuristique* sizeof(double));
    for (int k = 0; k < couleurHeuristique; k++) {
        pSommet->vecteurStochastique[k]=(1.0/couleurHeuristique);
    }
    listeSommet[index]=pSommet;
    printSommet(pSommet);
    printf("Vertex initialisation succeed\n\n");
}
Arbitre setArbitre(int tailleSommet,int tailleArret,int (*matrice)[tailleArret]){
    printf("Beginning of Arbitre initialisation\n");
    Arbitre pArbitre;
    pArbitre=malloc(2*sizeof(int)+sizeof(int*)+sizeof(Sommet*));
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
    for (int k = 0; k < couleurHeuristique; k++) {
        cumuleeP+=*(p+k);
        //printf("P%d: %lf\n",k, cumuleeP);
        if(thisP<cumuleeP) {
            //printf("k: %d\n", k);
            pSommet->couleur=k;
            printf("Coloriser Sommet %d par le couleur %d\n",pSommet->index,pSommet->couleur);
            printf("\n");
            return k;
        }
    }
    exit(-1);;
}
void colorier(){
    printf("\nBeginning of colorier\n");
    for(int a = 0; a < pArbitre->tailleSommet; a++){
        getCouleur(pArbitre->listeSommet[a]);
    }
    printf("End of colorier\n\n");
}
//conflit
int isConflit(Sommet unSommet,Sommet autreSommet){
    if(unSommet->couleur==autreSommet->couleur) return 1;
    return 0;
}
void calculerArretEtConflit(){
    printf("\nBeginning of calculerArretEtConflit\n");
    for(int b= 0; b<pArbitre->tailleSommet; b++){
        int countArrets=0,countConflits=0;
        for(int c= 0; c< pArbitre->tailleArret; c++){
            if(*(pArbitre->matrice+b*pArbitre->tailleArret+c)==1) {
                countArrets++;
                countConflits+=isConflit(pArbitre->listeSommet[b],pArbitre->listeSommet[c]);
            }
        }
        pArbitre->listeSommet[b]->nbrArrets=countArrets;
        pArbitre->listeSommet[b]->nbrConflits=countConflits;
        printIndex(pArbitre->listeSommet[b]);
        printNbrArrets(pArbitre->listeSommet[b]);
        printNbrConflits(pArbitre->listeSommet[b]);
        printf("\n");
    }
    printf("End of calculerArretEtConflit\n\n");
}
//calculer la taille Clique Maximale
int calculerCliqueMaximale(){

    return 3;
}
void calculercliqueMax(){
    for (int i = 0; i < tailleArret; ++i) {
        pArbitre->listeSommet[i]->cliqueMax=calculerCliqueMaximale();
    }
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