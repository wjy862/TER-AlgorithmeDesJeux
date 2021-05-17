#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define alpha 0.6
#define belta 0.5

double beneficeLocale(Sommet pSommet){
    int nbcoul_sous_graphe = pSommet->coul_ss_graph;
    double nbrconflits=(double)pSommet->nbrConflits;
    double nbrArrets=(double)pSommet->nbrArrets;
    double cliqueMaximale=(double)pSommet->cliqueMax;
    double benefice=(0.8*(1.0-(nbrconflits/nbrArrets)))+(0.2*(1-(abs(nbcoul_sous_graphe/*nbrCouleur*/-cliqueMaximale)/cliqueMaximale)* pow(0,(int)nbcoul_sous_graphe/*nbrCouleur*//(int)(2*cliqueMaximale))));
    printf("nbrconflits: %lf\n",nbrconflits);
    printf("nbrArrets: %lf\n",nbrArrets);
    printf("cliqueMaximale: %lf\n",cliqueMaximale);
    printf("beneficeLocale: %lf\n",benefice);
    /*printf("1-(nbrconflits/nbrArrets)): %lf\n",1-(nbrconflits/nbrArrets));
    printf("(1-(abs(nbrCouleur-cliqueMaximale)/cliqueMaximale): %lf\n",(1-(abs(nbrCouleur-cliqueMaximale)/cliqueMaximale)));
    printf("pow(0,(int)nbrCouleur/(int)(2*cliqueMaximale)): %f\n",pow(0,(int)nbrCouleur/(int)(2*cliqueMaximale)));*/
    return benefice;
}

double beneficeGlobale(){
    double benefice=1.0-(nbrCouleur/nbStrategies);
    printf("###nbStrategies: %lf\n",nbStrategies);
    printf("####nbrCouleur: %lf\n",nbrCouleur);
    printf("beneficeGlobal: %lf\n",benefice);
    return benefice;
}

double fonctionBenefice(Sommet pSommet){
    return alpha*beneficeLocale(pSommet)+belta*beneficeGlobale();
}
void updateBenefice(Sommet pSommet){
    printIndex(pSommet);
    pSommet->benefice=fonctionBenefice(pSommet);
    if(pSommet->benefice<pSommet->minBenefice) pSommet->minBenefice=pSommet->benefice;
    if(pSommet->benefice>pSommet->maxBenefice) pSommet->maxBenefice=pSommet->benefice;
    printf("\n");
}
void calculerBenefice(){
    printf("\nBeginning of calculerBenefice\n");
    nbStrategies=(double)couleurHeuristique;
    calculerNbrCouleurTotal();
    for (int i = 0; i < pArbitre->tailleSommet; ++i) {
        updateBenefice(pArbitre->listeSommet[i]);
    }
    printf("End of calculerBenefice\n\n");
}
