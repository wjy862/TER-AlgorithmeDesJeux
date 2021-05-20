void initMatriceRepartitionCouleurConflit(){
    for (int k = 0; k < tailleSommet; k++) {
        for (int m = 0; m < tailleArret; m++) {
            *(matriceRepartitionCouleurConflit+k*tailleArret+m)=0;
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
    return initGraphe();
}

int run(){
    /*Colorier le graphe selon la vecteur stochastique des sommets*/
    colorier();

    /*calculer des conflit de chaque sommet*/
    calculerConflit();

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
        //fprintf(F,"%d %d\n",tour,pArbitre->listeSommet[FPRINTSOMMET]->nbrConflits);
        if(tour%100 == 0)
        {
            fprintf(F,"%d %d\n",tour,calculerSommeConflits());
            fprintf(F1,"%d %d\n",tour,(int)nbrCouleur);
        }    }
    fclose(F);
    fclose(F1);
}
void commenceDuJeu(int nbrSommet, int count){
    /*Initialisation de l'arbitre*/
    pArbitre=initArbitre(initParametres(nbrSommet));

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