#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <time.h>

#define DEGRE 5
//#define FPRINTSOMMET 5
int tailleSommet=20;
int tailleArret=20;


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

struct Arbitre{
    int tailleSommet;
    int tailleArret;
    int *matrice;
    Sommet *listeSommet;
};
typedef struct Arbitre *Arbitre,A;

Arbitre pArbitre;
int couleurHeuristique;
double nbrCouleur;//Nombre total des couleurs dans la graphe
double nbStrategies;//(double) couleurHeuristique pour calculer

//prints
void printMatice(int thisTailleSommet,int thisTailleArret,int *thisMatrice){
    printf("tailleSommet: %d\n", thisTailleSommet);
    printf("tailleArret: %d\n", thisTailleArret);
    for (int k = 0; k < thisTailleSommet; k++) {
        for (int m = 0; m < thisTailleArret; m++) {
            printf("%d ", *(thisMatrice+k*thisTailleArret+m));
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
    //printf("Size of Arbitre: %ld\n", sizeof(pArbitre));//8
    //printf("Adresse of Arbitre : %d\n",pArbitre);
    //printf("Adresse of listeSommet: %d\n",(pArbitre->listeSommet[0]));
    printf("nombre total des Couleur: %lf",nbrCouleur);
    printMatice(pArbitre->tailleSommet,pArbitre->tailleArret,pArbitre->matrice);
    for (int i = 0; i < pArbitre->tailleSommet; i++) {
        printSommet(pArbitre->listeSommet[i]);
    }
    printf("End of printArbitre\n\n");
}

double calculerNbrCouleurTotal(){
    int *listCouleurs=malloc(tailleSommet*sizeof(int));//chaque index présente une couleur
    int count=0;
    for (int k = 0; k < tailleSommet; k++) {
        listCouleurs[k]=0;//initialiser
    }
    for (int i = 0; i < tailleSommet; i++) {
        listCouleurs[pArbitre->listeSommet[i]->couleur]++;//Si un sommet est coloriée par couleur 0 -> listCouleurs[0]++
    }

    for (int j = 0; j < tailleSommet; j++) {
        printf("Couleur %d est utilisé %d fois\n",j,listCouleurs[j]);
        if(listCouleurs[j]!=0) count++;//counter ce qui n'est pas 0 dans la list Couleurs
    }
    free(listCouleurs);
    nbrCouleur=(double)count;
    printf("Nombre total des couleurs dans la graphe: %lf\n",nbrCouleur);
    return nbrCouleur;
}


//initialisation
void initVecteurStochastique(){
    for (int index = 0; index < tailleArret; ++index) {
        pArbitre->listeSommet[index]->vecteurStochastique = malloc(couleurHeuristique * sizeof(double));
        for (int k = 0; k < couleurHeuristique; k++) {
            pArbitre->listeSommet[index]->vecteurStochastique[k] = (1.0 / couleurHeuristique);
        }
    }
}
void initSommet(int index,Sommet listeSommet[]){
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
    listeSommet[index]=pSommet;
    printSommet(pSommet);
    printf("Vertex initialisation succeed\n\n");
}
Arbitre initArbitre(int (*matrice)[tailleSommet]){
    printf("Beginning of Arbitre initialisation\n");
    Arbitre pArbitre;
    pArbitre=malloc(2*sizeof(int)+sizeof(int*)+sizeof(Sommet*));
    pArbitre->listeSommet=malloc(tailleSommet*sizeof(Sommet));
    if (!pArbitre||!pArbitre->listeSommet) exit(1);
    pArbitre->tailleSommet=tailleSommet;
    pArbitre->tailleArret=tailleArret;
    pArbitre->matrice=matrice[0];
    for (int i = 0; i < pArbitre->tailleSommet; i++) {
        initSommet(i,pArbitre->listeSommet);
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
        printf("P%d: %lf\n",k, cumuleeP);
        if(thisP<cumuleeP) {
            //printf("k: %d\n", k);
            pSommet->couleur=k;
            printf("Coloriser Sommet %d par le couleur %d\n",pSommet->index,pSommet->couleur);
            printf("\n");
            return k;
        }
    }
    printf("cumuleeP %lf is less than this p %lf",cumuleeP,thisP);
    exit(255);
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
void calculerArret(){
    printf("\nBeginning of calculerArret\n");
    for(int b= 0; b<pArbitre->tailleSommet; b++){
        int countArrets=0;
        for(int c= 0; c< pArbitre->tailleArret; c++){
            if(*(pArbitre->matrice+b*pArbitre->tailleArret+c)==1) {
                countArrets++;
            }
        }
        pArbitre->listeSommet[b]->nbrArrets=countArrets;
        printIndex(pArbitre->listeSommet[b]);
        printNbrArrets(pArbitre->listeSommet[b]);
        printf("\n");
    }
    printf("End of calculerArret\n\n");
}
void calculerConflit(){
    printf("\nBeginning of calculerConflit\n");
    for(int b= 0; b<pArbitre->tailleSommet; b++){
        int countConflits=0;
        for(int c= 0; c< pArbitre->tailleArret; c++){
            if(*(pArbitre->matrice+b*pArbitre->tailleArret+c)==1) {
                countConflits+=isConflit(pArbitre->listeSommet[b],pArbitre->listeSommet[c]);
            }
        }
        pArbitre->listeSommet[b]->nbrConflits=countConflits;
        printIndex(pArbitre->listeSommet[b]);
        printNbrConflits(pArbitre->listeSommet[b]);
        printf("\n");
    }
    printf("End of calculerConflit\n\n");
}
//calculer la taille Clique Maximale
int calculerCliqueMaximale(){
    return 3;
}
void calculercliqueMax(){
    for (int i = 0; i < tailleArret; i++) {
        pArbitre->listeSommet[i]->cliqueMax=calculerCliqueMaximale();
    }
}
//heuristiqueColoration
void printSommetsColorie(int *sommetsColorie,int tailleSommetsColorie){
    for (int i = 0; i < tailleSommetsColorie; i++) {
        printf("sommetsColorie[%d]: %d\n",i,sommetsColorie[i]);
    }
}
void printTailleSommetsColorie(int tailleSommetsColorie){
    printf("tailleSommetsColorie: %d\n",tailleSommetsColorie);
}
void printVoisinsNonColorie(int *voisinsNonColorie,int tailleVoisinNonColorie){
    for (int i = 0; i < tailleVoisinNonColorie; i++) {
        printf("voisinsNonColorie[%d]: %d\n",i,voisinsNonColorie[i]);
    }
}
void printTailleVoisinNonColorie(int tailleVoisinNonColorie){
    printf("tailleVoisinNonColorie: %d\n",tailleVoisinNonColorie);
}
int isVoisin(int ligne,int colonne){
    //printf("*(pArbitre->matrice+ligne*tailleArret+colonne): %d\n",*(pArbitre->matrice+ligne*tailleArret+colonne));
    return (*(pArbitre->matrice+ligne*tailleArret+colonne))==1;
}
/*0 si il existe dans la liste
 *1 si il n'existe pas dans las liste
 * */
int isDefferentFromAnyElements(int index,int *list,int taille){
    for (int k = 0; k < taille; k++) {
        if(list[k]==index) return 0;
    }
    return 1;
}
int findNbrVoisinNonColorie(int index,int *sommetsColorie,int tailleSommetsColorie){
    int count=0;
    for (int voisin = 0; voisin < tailleArret; voisin++) {//index arret
        if(isVoisin(index,voisin)){
            count+=isDefferentFromAnyElements(voisin,sommetsColorie,tailleSommetsColorie);
        }
    }
    printf("Chercher un voisin moins contraint, voisin: Sommet %d dont %d voisins non colorié\n",index,count);
    return count;
}

int getProchainVoisinLeMoinsContraint(int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie,int tailleVoisinNonColorie){
    //print la structure des parametre
    printTailleSommetsColorie(tailleSommetsColorie);
    printTailleVoisinNonColorie(tailleVoisinNonColorie);
    printSommetsColorie(sommetsColorie,tailleSommetsColorie);
    printVoisinsNonColorie(voisinsNonColorie,tailleVoisinNonColorie);

    int index;//index de sommet
    int max=RAND_MAX;//nombre de voisin non colorie
    for (int i = 0; i < tailleVoisinNonColorie; i++) {//index voisin
       int count=findNbrVoisinNonColorie(voisinsNonColorie[i],sommetsColorie,tailleSommetsColorie);
        if(count<max){
            max=count;
            index=voisinsNonColorie[i];
        }else if(count=max){
            index=unif()<0.5?index:voisinsNonColorie[i];
        }
    }
    return index;
}
void heuristiqueColorier(int index,int *sommetsColorie,int tailleSommetsColorie){
    int *listecouleur= malloc(tailleArret* sizeof(int));
    for (int t = 0; t < tailleSommet; t++) {
        listecouleur[t]=0;
    }
    for (int voisin = 0; voisin < tailleArret; voisin++) {
        if(isVoisin(index,voisin)){
            if(isDefferentFromAnyElements(voisin,sommetsColorie,tailleSommetsColorie)==0){
                listecouleur[pArbitre->listeSommet[voisin]->couleur]++;
            }
        }
    }
    for (int i = 0; i < tailleArret; i++) {
       if(listecouleur[i]==0){
           pArbitre->listeSommet[index]->couleur=i;
           printf("Sommet %d est le voisin moins contraint, colorié par couleur: %d\n\n",pArbitre->listeSommet[index]->index,i);
           break;
       }
    }
    free(listecouleur);
}
int* trouverListeVoisin(int *sommetsColorie,int tailleSommetsColorie){
    /*si trouver un voisin liste[voisin]++,eliminer les sommets Colorie à la fin*/
    int *listeVoisin=malloc(tailleArret* sizeof(int));
    for (int t = 0; t < tailleSommet; t++) {
        listeVoisin[t]=0;
    }
    for (int index = 0; index < tailleSommetsColorie; index++) {
        for (int voisin = 0; voisin < tailleArret; voisin++) {
            if(isVoisin(sommetsColorie[index],voisin)) {
                listeVoisin[voisin]++;
                //printf("sommet %d sont voisin de sommet %d\n",index,voisin);
            }else{
                //printf("sommet %d ne sont pas voisin de sommet %d\n",index,voisin);
            }
        }
    }
    for (int index = 0; index < tailleSommetsColorie; index++) {
        listeVoisin[sommetsColorie[index]]=0;
        //printf("sommet %d ont colorié\n", sommetsColorie[index]);
    }
    return listeVoisin;
}
int calculerTailleVoisinNonColorie(int *sommetsColorie,int tailleSommetsColorie){
    int count=0;
    int *listeVoisin= trouverListeVoisin(sommetsColorie,tailleSommetsColorie);
    for (int t = 0; t < tailleArret; t++) {
        if(listeVoisin[t]!=0) count++;
    }
    free(listeVoisin);
    return count;
}
int* calculerVoisinsNonColorie(int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie){
    int count=0;
    int *listeVoisin= trouverListeVoisin(sommetsColorie,tailleSommetsColorie);
    for (int t = 0; t < tailleSommet; t++) {
        voisinsNonColorie[t]=0;
        if(listeVoisin[t]!=0) voisinsNonColorie[count++]=t;
    }
    free(listeVoisin);
    return voisinsNonColorie;
}
int heuristiqueColoriser(int count,int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie,int tailleVoisinNonColorie){
    if(count==0) return count;
    printf("\nA tour %d,il reste %d sommets non colorié\n",tailleSommet-count,count);
    int voisin=getProchainVoisinLeMoinsContraint(sommetsColorie,tailleSommetsColorie,voisinsNonColorie,tailleVoisinNonColorie);
    heuristiqueColorier(voisin,sommetsColorie,tailleSommetsColorie);
    tailleSommetsColorie++;
    sommetsColorie[tailleSommetsColorie-1]=voisin;
    tailleVoisinNonColorie=calculerTailleVoisinNonColorie(sommetsColorie,tailleSommetsColorie);
    voisinsNonColorie=calculerVoisinsNonColorie(sommetsColorie,tailleSommetsColorie,voisinsNonColorie);
    count--;
    count=heuristiqueColoriser(count,sommetsColorie,tailleSommetsColorie,voisinsNonColorie,tailleVoisinNonColorie);
    return count;
}

int initNbrColoration(){
    printf("\nBeginning of heuristiqueColoration\n");
    int couleurmax=0;
    int count=tailleArret;
    //choisir un sommet par hasard puis colorier
    int indexPremierSommet=(int)(unif()*tailleSommet);
    printf("Sommet %d est la premier sommet colorié par couleur: %d\n",indexPremierSommet,0);
    pArbitre->listeSommet[indexPremierSommet]->couleur=0;
    count--;
    //création des parametres
    int tailleSommetsColorie,tailleVoisinNonColorie;
    int *sommetsColorie= malloc(tailleArret* sizeof(int));
    int *voisinsNonColorie= malloc(tailleArret* sizeof(int));
    for (int i = 0; i < tailleSommet; i++) {
        sommetsColorie[i]=0;
        voisinsNonColorie[i]=0;
    }
    //initialisation des parametres
    sommetsColorie[0]=indexPremierSommet;
    tailleSommetsColorie=1;
    tailleVoisinNonColorie= calculerTailleVoisinNonColorie(sommetsColorie,tailleSommetsColorie);
    voisinsNonColorie=calculerVoisinsNonColorie(sommetsColorie,tailleSommetsColorie,voisinsNonColorie);
    //print la structure des parametre
    printTailleSommetsColorie(tailleSommetsColorie);
    printTailleVoisinNonColorie(tailleVoisinNonColorie);
    printSommetsColorie(sommetsColorie,tailleSommetsColorie);
    printVoisinsNonColorie(voisinsNonColorie,tailleVoisinNonColorie);
    //colorier les voisin
    heuristiqueColoriser(count,sommetsColorie,tailleSommetsColorie,voisinsNonColorie,tailleVoisinNonColorie);
    //calculer Nbr Couleur Total
    couleurHeuristique=(int)calculerNbrCouleurTotal();
    //remettre les valeur
    for (int i = 0; i < tailleSommet; i++) {
        pArbitre->listeSommet[i]->couleur=-1;
    }
    //free les memoires
    free(sommetsColorie);
    free(voisinsNonColorie);
    printf("\nEnd of heuristiqueColoration\n");
    return couleurHeuristique;
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