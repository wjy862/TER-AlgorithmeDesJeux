#include "graphe.h"
#include "sommet.h"
#include "benefice.h"

int tailleSommet=5;
int tailleArret=5;
int matrice[TSOMMET][TARRET]={
        {0,1,1,0,0},
        {1,0,1,0,1},
        {1,1,0,1,0},
        {0,0,1,0,1},
        {0,1,0,1,0}
};
int cliqueMaximale=3;


int main() {
    /*Génerer un graphe*/
    nbr_Vertices = 4;
    printf("nb_sommets:%d\n", nbr_Vertices);
    array_Ty *Matrix1 = CreateMatrix();
    array_Ty *Matrix2 = CreateMatrix_vide();
    FairCopiedeMatrix(Matrix1, Matrix2, nbr_Vertices);
    PrintMatrix(Matrix2, nbr_Vertices);

    /*Trouver un nombre de coloration propre par heursitique*/
    couleur=heuristiqueColoration(tailleArret,matrice);

    /*Initialisation de l'arbitre*/
    Arbitre pArbitre=setArbitre(tailleSommet,tailleArret,matrice);

    /*Colorier le graphe selon la vecteur stochastique des sommets*/
    Clorier(pArbitre);

    /*calculer des conflit de chaque sommet*/
    calculerConflit(pArbitre);

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
