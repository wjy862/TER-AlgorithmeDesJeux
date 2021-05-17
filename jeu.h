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
void commenceDuJeu(){
    FILE *F,*F1;
    F = fopen("jeuConflit.data","w");
    F1 = fopen("jeuCouleur.data","w");
    for (int tour = 0; tour < N; tour++) {
        if(run()==1) break;//run()==1, si max probability > threshold (typically 0.999) -> equilibre de nash
        int sommeConflits=0;
        for (int i = 0; i < tailleSommet; i++) {
            sommeConflits+=pArbitre->listeSommet[i]->nbrConflits;
        }
        //fprintf(F,"%d %d\n",tour,pArbitre->listeSommet[FPRINTSOMMET]->nbrConflits);
        fprintf(F,"%d %d\n",tour,sommeConflits);
        fprintf(F1,"%d %d\n",tour,(int)nbrCouleur);
    }
    fclose(F);
    fclose(F1);
}
