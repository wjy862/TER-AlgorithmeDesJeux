#include "sommet.h"
#include "graphe.h"
#include "benefice.h"
#include "apprendissage.h"
#include "jeu.h"

/*free les mémoires*/
void freeAll();

int main() {
    /*Génerer un graphe*/
    int* matrice =initGraphe();

    /*Initialisation de l'arbitre*/
    pArbitre=initArbitre(matrice);

    /*initialisation du nembre des Couleur, trouver un nombre de coloration propre par heursitique*/
    initNbrColoration();

    /*Initialisation des vecteurStochastique*/
    initVecteurStochastique();

    /*calculer la taille de clique maximale de chaque sommet*/
    calculercliqueMax();

    /*calculer la taille de clique maximale de chaque sommet*/
    calculerArret();

    /*commence du jeu*/
    commenceDuJeu();

    /*Imprimer tout la stucture Arbitre*/
    printArbitre();

    /*free les mémoires*/
    freeAll();

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