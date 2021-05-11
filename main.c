#include "sommet.h"


int matrice[I][J]={
        {5,5,0,0,0},
        {0,0,1,1,0},
        {0,0,1,1,1},
        {1,0,0,1,1},
        {1,0,1,0,1},
        {0,0,1,1,0}
};

int main() {
    Arbitre pArbitre=setArbitre(matrice);
    Clorier(pArbitre);
    printf("Debut test de l'initialisation du setArbitre\n");
    printf("%ld\n", sizeof(pArbitre));//8
    for (int k = 0; k < I; k++) {
        for (int m = 0; m < J; m++) {
            printf("%d ", *(*(pArbitre->matrice+k)+m));//5
        }
        printf("\n");
    }
    for (int i = 0; i < J; i++) {
        printf("pArbitre->listeSommet[%d]->index: %d\n", i,(pArbitre->listeSommet[i]->index));//0
        printf("pArbitre->listeSommet[%d]->couleur: %d\n", i,(pArbitre->listeSommet[i]->couleur));//-1
        for (int y = 0; y < COULEUR; y++) {
            printf("*(pArbitre->listeSommet[%d]->vecteurStochastique %d): %lf\n", i, y,*(pArbitre->listeSommet[i]->vecteurStochastique + y));
        }
    }
    printf("Fin du test de l'initialisation du setArbitre\n");
    return 0;
}
