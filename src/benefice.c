#include "../inc/benefice.h"
#include "../inc/struct.h"

double beneficeLocale(Sommet pSommet){
    int nbcoul_sous_graphe = pSommet->coul_ss_graph;
    double nbrconflits=(double)pSommet->nbrConflits;
    double nbrArrets=(double)pSommet->nbrArrets;
    int cliqueMaximale=pSommet->cliqueMax;
    if(nbrArrets==0||cliqueMaximale==0) exit(246);//denominateur ne peut etre 0
    //double benefice=(1.0-(nbrconflits/nbrArrets));

    //double benefice=(1.0-(nbrconflits/nbrArrets))*(1-(abs(nbrCouleur-cliqueMaximale)/cliqueMaximale)* pow(0,(int)nbrCouleur/(int)(2*cliqueMaximale)));
    //printf("nbrconflits: %lf\n",nbrconflits);
    //printf("nbrArrets: %lf\n",nbrArrets);
    //printf("cliqueMaximale: %lf\n",cliqueMaximale);
    //printf("beneficeLocale: %lf\n",benefice);


    double benefice=(0.8*(1.0-(nbrconflits/nbrArrets)))+(0.2*(1-(abs(nbcoul_sous_graphe/*nbrCouleur*/-cliqueMaximale)/cliqueMaximale)* pow(0,(int)nbcoul_sous_graphe/*nbrCouleur*//(int)(2*cliqueMaximale))));
    //printf("nbrconflits: %lf\n",nbrconflits);
    //printf("nbrArrets: %lf\n",nbrArrets);
    //printf("cliqueMaximale: %lf\n",cliqueMaximale);
    //printf("beneficeLocale: %lf\n",benefice);

    /*printf("1-(nbrconflits/nbrArrets)): %lf\n",1-(nbrconflits/nbrArrets));
    printf("(1-(abs(nbrCouleur-cliqueMaximale)/cliqueMaximale): %lf\n",(1-(abs(nbrCouleur-cliqueMaximale)/cliqueMaximale)));
    printf("pow(0,(int)nbrCouleur/(int)(2*cliqueMaximale)): %f\n",pow(0,(int)nbrCouleur/(int)(2*cliqueMaximale)));*/
    return benefice;
}

double beneficeGlobale(){
    if(nbStrategies==0) exit(247);//denominateur ne peut etre 0
    double benefice=1.0-(nbrCouleur/nbStrategies);
    //printf("###nbStrategies: %lf\n",nbStrategies);
    //printf("####nbrCouleur: %lf\n",nbrCouleur);
    //printf("beneficeGlobal: %lf\n",benefice);
    return benefice;
}

double fonctionBenefice(Sommet pSommet){
    return alpha*beneficeLocale(pSommet)+belta*beneficeGlobale();
}
void updateBenefice(Sommet pSommet){
    //printIndex(pSommet);
    pSommet->benefice=fonctionBenefice(pSommet);
    if(pSommet->benefice<pSommet->minBenefice) pSommet->minBenefice=pSommet->benefice;
    if(pSommet->benefice>pSommet->maxBenefice) pSommet->maxBenefice=pSommet->benefice;
    //printf("pSommet->benefice %lf, pSommet->minBenefice %lf, pSommet->maxBenefice %lf\n", pSommet->benefice,pSommet->minBenefice,pSommet->maxBenefice);
    //printf("\n");

}
void calculerBenefice(){
    //printf("\nBeginning of calculerBenefice\n");
    nbStrategies=(double)couleurHeuristique;

    for (int i = 0; i < pArbitre->tailleSommet; ++i) {
        updateBenefice(pArbitre->listeSommet[i]);
    }
    //printf("End of calculerBenefice\n\n");
}
