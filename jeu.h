#include <unistd.h>

void initMatriceRepartitionCouleurConflit(){
    for (int k = 0; k < maxTailleSommet+1; k++) {
        for (int m = 0; m < (((maxTailleSommet-1)*(maxTailleSommet))/2); m++) {
            *(matriceRepartitionCouleurConflit+k*(((maxTailleSommet-1)*(maxTailleSommet))/2)+m)=0;
        }
    }
}
int* initParametres(int nbrSommet){
    /*redéfinir la taille du sommet et arret*/
    tailleSommet=tailleArret=nbrSommet;
    /*remettre nbrColorationPropre à 0 pour chaque graphe*/
    nbrColorationPropre=0;
    /*initialisation du matriceRepartitionCouleurConflit [couleur][conflit]*/
    initMatriceRepartitionCouleurConflit();
    /*Génerer un graphe*/
    int *matrice=initGraphe();
    int count=0;
    while(tailleSommet!=nbrSommet){
        count++;
        if(count>=10) {
            printf("Echec à generer un graphe de sommet %d avec un degre de %d après 10 fois essais\n");
            break;
        }else{
            matrice=initGraphe();
        }
    }
    return matrice;
}

int run(){
    /*Colorier le graphe selon la vecteur stochastique des sommets*/
    colorier();

    /*calculer des conflit de chaque sommet*/
    calculerConflit();

    /*calculer nb couleur de l'emsemble du graphe*/
    calculerNbrCouleurTotal();

    /*calculer les couleurs des sous graphes*/
    calculerCouleurSsgraphe();

    /*calculer des bénéfice de chaque sommet*/
    calculerBenefice();

    /*Reinforcement learning*/
    return updateVecteurStochastique();//return 1, si max probability > threshold (typically 0.999) -> equilibre de nash
}
void commenceColoration(){
    FILE *F,*F1;
    F = fopen("Conflicts.data","w");
    F1 = fopen("Colors.data","w");
    for (int tour = 0; tour < N; tour++) {
        if(run()==1) break;//run()==1, si max probability > threshold (typically 0.999) -> equilibre de nash
        //if(tour%100 == 0)
        {
            fprintf(F,"%d %d\n",tour,calculerSommeConflits());
            fprintf(F1,"%d %d\n",tour,(int)nbrCouleur);
        }
    }
    fclose(F);
    fclose(F1);
}
void commenceDuJeu(int *matrice, int count){
    /*Initialisation de l'arbitre*/
    pArbitre=initArbitre(GRAPHE);//#define GRAPHE matrice

    /*initialisation du membre des Couleur, trouver un nombre de coloration propre par heursitique*/
    initNbrColoration();

    /*Initialisation des vecteurStochastique*/
    initVecteurStochastique();

    /*calculer la taille de clique maximale de chaque sommet*/
    calculercliqueMax();

    /*calculer la nombre de Arret de chaque sommet*/
    calculerArret();

    /*commence du coloration*/
    commenceColoration();

    /*calculer Nbr fois qu'on a atteind Coloration Propre*/
    calculerNbrColorationPropre(count);

    /*calculer Nbr fois qu'on a des meme couleurs et des meme conflits lors de*/
    calculerNbrCouleursEtNbrConflits();

    /*Imprimer tout la stucture Arbitre*/
    //printArbitre();
    //printMatice(matrice);
    //printMatice(pArbitre->matrice);
    //sleep(2);

    /*free les mémoires*/
    freeAll();
}
void freeAll(){
    for (int i = 0; i < tailleArret; ++i) {
        free(pArbitre->listeSommet[i]->vecteurStochastique);
        free(pArbitre->listeSommet[i]);
    }
    free(pArbitre->listeSommet);
    free(pArbitre);
}

void  resetSommet(Sommet pSommet){
    pSommet->couleur=-1;
    pSommet->nbrConflits=-1;
    pSommet->benefice=0.0;
    pSommet->maxBenefice=0.0;
    pSommet->minBenefice=0.0;
    pSommet->cliqueMax=-1;
    pSommet->nbrArrets=-1;
    pSommet->coul_ss_graph = 0;
}
void resetArbitre(){
    for (int i = 0; i < pArbitre->tailleSommet; i++) {
        free(pArbitre->listeSommet[i]->vecteurStochastique);
        resetSommet(pArbitre->listeSommet[i]);
    }

}