#include "sommet.h"
#include "graphe.h"
#include "benefice.h"
#include "apprendissage.h"
#include "jeu.h"

#define TIMES 1
/*free les mémoires*/
void freeAll();

int main() {
    int maxTailleSommet=tailleSommet;

    /*générer des graphes de 2 sommets à 20 sommets, puis calculer le nombre des fois qu'on obetient une coloration propre*/
    for (int nbrSommet = 2; nbrSommet <= maxTailleSommet; nbrSommet++) {

        /*remettre nbrColorationPropre à 0 pour chaque graphe*/
        nbrColorationPropre=0;

        /*redéfinir la taille du sommet et arret*/
        tailleSommet=tailleArret=nbrSommet;
        printf("tailleSommet: %d, tailleSommet: %d\n",tailleSommet,tailleArret);
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

            /*calculer Nbr Coloration Propre*/
            calculerNbrColorationPropre(i);

            /*Imprimer tout la stucture Arbitre*/
            //printArbitre();

            /*free les mémoires*/
            freeAll();
        }

        /*nbr des fois obtenu une coloration propre après TIMES fois du jeu*/
        printNbrColorationPropre(nbrSommet,(double)nbrColorationPropre/(double)TIMES);
    }

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