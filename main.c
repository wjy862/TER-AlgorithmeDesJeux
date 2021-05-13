#include "graphe.h"
#include "sommet.h"
#include "benefice.h"



int main() {
    /*Génerer un graphe*/
   /* nbr_Vertices = 7;
    printf("nb_sommets:%d\n", nbr_Vertices);
    array_Ty *Matrix1 = CreateMatrix();
    array_Ty *Matrix2 = CreateMatrix_vide();
    FairCopiedeMatrix(Matrix1, Matrix2, nbr_Vertices);
    PrintMatrix(Matrix2, nbr_Vertices);*/

    /*Trouver un nombre de coloration propre par heursitique*/
    couleurHeuristique=heuristiqueColoration(tailleArret,matrice);

    /*Initialisation de l'arbitre*/
    pArbitre=setArbitre(tailleSommet,tailleArret,matrice);

    /*Colorier le graphe selon la vecteur stochastique des sommets*/
    colorier(pArbitre);

    /*calculer des conflit de chaque sommet*/
    calculerArretEtConflit(pArbitre);

    /*calculer la taille de clique maximale de chaque sommet*/
    calculerCliqueMaximale();

    /*calculer des bénéfice de chaque sommet*/
    calculerBenefice(pArbitre);

    /*Imprimer tout la stucture Arbitre*/
    printArbitre(pArbitre);

    /*free les mémoires*/
    for (int i = 0; i < tailleArret; ++i) {
        free(pArbitre->listeSommet[i]->vecteurStochastique);
        free(pArbitre->listeSommet[i]);
    }
    free(pArbitre->listeSommet);
    free(pArbitre);
    return 0;
}
