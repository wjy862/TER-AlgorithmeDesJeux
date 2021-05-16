int run(){
    /*Colorier le graphe selon la vecteur stochastique des sommets*/
    colorier();

    /*calculer des conflit de chaque sommet*/
    calculerConflit();

    /*calculer des bénéfice de chaque sommet*/
    calculerBenefice();

    /*Reinforcement learning*/
    return updateVecteurStochastique();//return 1, si max probability > threshold (typically 0.999) -> equilibre de nash
}
void commenceDuJeu(){
    FILE *F;
    F = fopen("jeu.data","w");
    for (int tour = 0; tour < N; tour++) {
        if(run()==1) break;//run()==1, si max probability > threshold (typically 0.999) -> equilibre de nash
        fprintf(F,"%d %lf\n",tour,(double)pArbitre->listeSommet[FPRINTSOMMET]->nbrConflits);
    }

    fclose(F);
}
