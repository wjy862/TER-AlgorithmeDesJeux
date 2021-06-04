#include "../inc/jeu.h"
#include "../inc/sommet.h"
#include "../inc/benefice.h"
#include "../inc/graphe.h"
#include "../inc/apprentissage.h"
#include "../inc/struct.h"

void initMatriceRepartitionCouleurConflit(){
    for (int k = 0; k < maxTailleSommet+1; k++) {
        for (int m = 0; m < (((maxTailleSommet-1)*(maxTailleSommet))/2); m++) {
            *(matriceRepartitionCouleurConflit+k*(((maxTailleSommet-1)*(maxTailleSommet))/2)+m)=0;
        }
    }
}
int* initParametres(int nbrSommet,int minDegre){
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
            printf("Echec à generer un graphe de sommet %d avec un degre de %d après 10 fois essais\n",nbrSommet,minDegre);
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

int nash()
{
    int couleur = 0; 
    double tmp = 0.0;
    //double benefice = 0.0;
    double utilite = 0.0;
    for(int i =0;i<pArbitre->tailleSommet;i++)
    {
        couleur = pArbitre->listeSommet[i]->couleur;
        utilite = calculerUtilite(pArbitre->listeSommet[i]);
            for(int j =0;j<(int)nbrCouleur;j++)
            {
                if(j == couleur) continue;
                pArbitre->listeSommet[j]->couleur = j;
                pArbitre->listeSommet[j]->benefice = fonctionBenefice(pArbitre->listeSommet[j]);
                tmp = calculerUtilite(pArbitre->listeSommet[j]);
                 
                if((utilite - tmp) < 0.0)
                {
                    //printf("%lf\n",utilite-tmp);
                    pArbitre->listeSommet[j]->couleur = couleur;
                    return 0;
                }
            }
        pArbitre->listeSommet[i]->couleur = couleur;

    }
    return 1;
}

void commenceColoration(){
    FILE *F,*F1;
    F = fopen("data/Conflicts.data","w");
    F1 = fopen("data/Colors.data","w");
    for (int tour = 0; tour < N; tour++) {
        if(run()==1) break;//run()==1, si max probability > threshold (typically 0.999) -> equilibre de nash
        if(tour%100 == 0)
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
    pArbitre=initArbitre(matrice);//#define GRAPHE matrice

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
    //freeAll();
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