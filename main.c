#include "parametre.h"
#include "sommet.h"
#include "graphe.h"
#include "benefice.h"
#include "apprendissage.h"
#include "jeu.h"




/*free les mémoires*/
void freeAll();

int main() {

    /*générer des graphes de 2 sommets à 20 sommets, puis calculer le nombre des fois qu'on obetient une coloration propre*/
    int maxTailleSommet=tailleSommet;
    matriceCouleurConflit= malloc(tailleSommet*tailleArret*sizeof(int));
    for (int nbrSommet = 3; nbrSommet <= maxTailleSommet; nbrSommet++) {
        /*initialisation du matrice [ccouleur][conflit]*/
        for (int k = 0; k < tailleSommet; k++) {
            for (int m = 0; m < tailleArret; m++) {
                *(matriceCouleurConflit+k*tailleArret+m)=0;
            }

        }
        /*remettre nbrColorationPropre à 0 pour chaque graphe*/
        nbrColorationPropre=0;

        /*redéfinir la taille du sommet et arret*/
        tailleSommet=tailleArret=nbrSommet;
        //printf("tailleSommet: %d, tailleSommet: %d\n",tailleSommet,tailleArret);

        /*Génerer un graphe*/
        int* matrice =initGraphe();

        /*répéter TIMES fois le jeu à trouver equilibre de nash*/
        for (int i = 0; i < TIMES; i++) {
            /*Initialisation de l'arbitre*/
            pArbitre=initArbitre(matrice);

            /*initialisation du membre des Couleur, trouver un nombre de coloration propre par heursitique*/
            initNbrColoration();

            /*Initialisation des vecteurStochastique*/
            initVecteurStochastique();

            /*calculer la taille de clique maximale de chaque sommet*/
            calculercliqueMax();

            /*calculer la nombre de Arret de chaque sommet*/
            calculerArret();

            /*commence du coloration*/
            commenceDuJeu();

            /*calculer Nbr fois qu'on a atteind Coloration Propre*/
            calculerNbrColorationPropre(i);

            /*calculer Nbr fois qu'on a des meme couleurs et des meme conflits lors de*/
            calculerNbrCouleursEtNbrConflits();

            /*Imprimer tout la stucture Arbitre*/
            //printArbitre();

            /*free les mémoires*/
            freeAll();
        }
        printNbrCouleursEtNbrConflits();
        /*nbr des fois obtenu une coloration propre après TIMES fois du jeu*/
        printNbrColorationPropre(tailleSommet,(double)nbrColorationPropre/(double)TIMES);
    }
    free(matriceCouleurConflit);
    return 0;
}

void freeAll(){
    for (int i = 0; i < tailleArret; ++i) {
        free(pArbitre->listeSommet[i]->vecteurStochastique);
        free(pArbitre->listeSommet[i]);
    }
    free(pArbitre->listeSommet);
    free(pArbitre);

}