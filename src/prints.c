#include "../inc/prints.h"
#include "../inc/struct.h"

//prints
/*int*/void printMatice(int thisTailleSommet,int thisTailleArret,int *thisMatrice){
    //printf("tailleSommet: %d\n", thisTailleSommet);
    //printf("tailleArret: %d\n", thisTailleArret);
    for (int k = 0; k < thisTailleSommet; k++) {
        for (int m = 0; m < thisTailleArret; m++) {
            printf("%d ", *(thisMatrice+k*tailleArret+m));
        }
        printf("\n");
    }
    //return 1;
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
void printCouleurSousgraphe(Sommet pSommet)
{
    printf("this coulssgraph: %d\n", pSommet->coul_ss_graph);
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
    printCouleurSousgraphe(pSommet);
}
void printArbitre(){
    printf("\nBeginning of printArbitre\n");
    //printf("Size of Arbitre: %ld\n", sizeof(pArbitre));//8
    //printf("Adresse of Arbitre : %d\n",pArbitre);
    //printf("Adresse of listeSommet: %d\n",(pArbitre->listeSommet[0]));
    //printf("nombre total des Couleur: %lf",nbrCouleur);
    printMatice(tailleSommet,tailleArret,pArbitre->matrice);
    for (int i = 0; i < pArbitre->tailleSommet; i++) {
        printSommet(pArbitre->listeSommet[i]);
    }
    int sommeConflits=calculerSommeConflits();
    printf("somme du nombre des Conflits: %d\n",sommeConflits);
    printf("nombre total des Couleur: %d\n",(int)nbrCouleur);
    printf("End of printArbitre\n\n");
}
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
void printNbrCouleursEtNbrConflits(){
    //mettre en base pour fprint
}
void printNbrColorationPropre(int nbrSommet,double pourcentage){
    //FILE *F3;
    //F3 = fopen("logs1.data","a+");
    printf("Lors d'attaindre l'équilibre de nash %d fois\n",TIMES);
    //fprintf(F3,"Lors d'attaindre l'équilibre de nash %d fois\n",TIMES);
    for (int k = 1; k < couleurHeuristique+1; k++) {
        for (int m = 0; m < (((maxTailleSommet-1)*(maxTailleSommet))/2); m++) {
            if((*(matriceRepartitionCouleurConflit+k*(((maxTailleSommet-1)*(maxTailleSommet))/2)+m))==0) continue;
            printf("(nb couleurs: %d, nb conflits: %d) apparait %d fois\n", k,m,(*(matriceRepartitionCouleurConflit+k*(((maxTailleSommet-1)*(maxTailleSommet))/2)+m)));
            //fprintf(F3,"(nb couleurs: %d, nb conflits: %d) apparait %d fois\n", k,m,(*(matriceRepartitionCouleurConflit+k*(((maxTailleSommet-1)*(maxTailleSommet))/2)+m)));
        }
    }

    int minColorationPropre=calculerMinColorationPropre();
    printf("Graphe de %d sommets (moyen degre: %d), nbColorationPropre obtenue est de %d avec minCouleurs de %d, tauxColorationPropre est de %lf\n\n\n",nbrSommet,minDegre,nbrColorationPropre,minColorationPropre,pourcentage);
    //fprintf(F3,"Graphe de %d sommets (moyen degre: %d), nbColorationPropre obtenue est de %d avec minCouleurs de %d, tauxColorationPropre est de %lf\n\n\n",nbrSommet,minDegre,nbrColorationPropre,1,pourcentage);
    //fclose(F3);
   }

/*apprendissage.h*/
void printR(double r){
    printf("Number of actions: %lf\n",r);
}
void printA(double a){
    printf("this action: %lf\n",a);
}
void printP(double p){
    printf("Probability vector: %lf\n",p);
}
void printUtilite(double utilite){
    printf("Environmental response (P,Q,S): %lf\n",utilite);
}
void printProbabilite(Sommet pSommet,int index){
    printf("pour sommet %d, la couleur %d a une proba de: %lf\n",pSommet->index,index,pSommet->vecteurStochastique[index]);
}