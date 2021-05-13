#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define alpha 0.5
#define belta 0.5

double nbrCouleur;//Nombre total des couleurs dans la graphe
double nbStrategies;

void calculerNbrCouleurTotal(Arbitre pArbitre){
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
}

double beneficeLocal(Sommet pSommet){
    double nbrconflits=(double)pSommet->nbrConflits;
    double nbrArrets=(double)pSommet->nbrArrets;
    double cliqueMaximale=(double)pSommet->cliqueMaximale;
    printf("nbrconflits: %lf\n",nbrconflits);
    printf("nbrArrets: %lf\n",nbrArrets);
    printf("cliqueMaximale: %lf\n",cliqueMaximale);
    printf("1-(nbrconflits/nbrArrets)): %lf\n",1-(nbrconflits/nbrArrets));
    printf("(1-(abs(nbrCouleur-cliqueMaximale)/cliqueMaximale): %lf\n",(1-(abs(nbrCouleur-cliqueMaximale)/cliqueMaximale)));
    printf("pow(0,(int)nbrCouleur/(int)(2*cliqueMaximale)): %f\n",pow(0,(int)nbrCouleur/(int)(2*cliqueMaximale)));
    return (1.0-(nbrconflits/nbrArrets))*(1-(abs(nbrCouleur-cliqueMaximale)/cliqueMaximale)* pow(0,(int)nbrCouleur/(int)(2*cliqueMaximale)));
}

double beneficeGlobal(){
    printf("nbStrategies: %lf\n",nbStrategies);
    printf("nbrCouleur: %lf\n",nbrCouleur);
    printf("beneficeGlobal: %lf\n",1.0-(nbrCouleur/nbStrategies));
    return 1.0-(nbrCouleur/nbStrategies);
}

double fonctionBenefice(Sommet pSommet,Arbitre pArbitre){
    return alpha*beneficeLocal(pSommet)+belta*beneficeGlobal();
}
void updateBenefice(Sommet pSommet,Arbitre pArbitre){
    printIndex(pSommet);
    pSommet->benefice=fonctionBenefice(pSommet,pArbitre);
    if(pSommet->benefice<pSommet->minBenefice) pSommet->minBenefice=pSommet->benefice;
    if(pSommet->benefice>pSommet->maxBenefice) pSommet->maxBenefice=pSommet->benefice;
    printf("\n");
}
void calculerBenefice(Arbitre pArbitre){
    printf("\nBeginning of calculerBenefice\n");
    nbStrategies=(double)couleurHeuristique;
    calculerNbrCouleurTotal(pArbitre);
    for (int i = 0; i < pArbitre->tailleSommet; ++i) {
        updateBenefice(pArbitre->listeSommet[i],pArbitre);
    }
    printf("End of calculerBenefice\n\n");
}
