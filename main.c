#include "graphe.h"
#include "sommet.h"
#include "benefice.h"
#include "apprendissage.h"


int main() {
    /*Génerer un graphe*/
    //int *matrice=genererUnGraphe();//int matrice[][], int tailleSommet int tailleArret

    /*Initialisation de l'arbitre*/
    pArbitre=setArbitre(tailleSommet,tailleArret,matrice);

    /*Trouver un nombre de coloration propre par heursitique*/
    heuristiqueColoration();

    /*Initialisation des vecteurStochastique*/
    setVecteurStochastique();

    /*Colorier le graphe selon la vecteur stochastique des sommets*/
    colorier();

    /*calculer des conflit de chaque sommet*/
    calculerArretEtConflit();

    /*calculer la taille de clique maximale de chaque sommet*/
    calculercliqueMax();

    /*calculer des bénéfice de chaque sommet*/
    calculerBenefice();

    /*Imprimer tout la stucture Arbitre*/
    printArbitre();

    /*free les mémoires*/
    for (int i = 0; i < tailleArret; ++i) {
        free(pArbitre->listeSommet[i]->vecteurStochastique);
        free(pArbitre->listeSommet[i]);
    }
    free(pArbitre->listeSommet);
    free(pArbitre);
    return 0;
}
