//#include "sommet.h"
#include "graphe.h"
//#include "benefice.h"
//#include "apprendissage.h"
//#include "jeu.h"

/*free les mémoires*/
void freeAll();

int main() {
    nbr_Vertices = rand();
    printf("nb_sommets_audebut:%d\n", nbr_Vertices);
    array_Ty *Matrix1 = CreateMatrix();
    array_Ty *Matrix2 = CreateMatrix_vide(nbr_Vertices);
    array_Ty *MatrixFinalConnexe;
    array_Ty *Matrix_forcee = CreateMatrix_forcee(nbr_Vertices);
    FairCopiedeMatrix(Matrix1, Matrix2, nbr_Vertices);

    array_Ty *Matrixsommetsnonconnexes = Prendre_sommetsnonconnexes(Matrix2, nbr_Vertices);
    nbr_sommets_non_connexes = Nombre_effacer_sommets(Matrixsommetsnonconnexes, nbr_Vertices);
    nbr_Vertices_nouvelle = nbr_Vertices - nbr_sommets_non_connexes;
    if (nbr_Vertices_nouvelle > 0 && nbr_Vertices_nouvelle < nbr_Vertices)
    {
        printf("Matrice Connexe\n");
        MatrixFinalConnexe = GenerationMatriceconnexe(Matrix2, Matrixsommetsnonconnexes, nbr_Vertices, nbr_Vertices_nouvelle);
        PrintMatrix(MatrixFinalConnexe, nbr_Vertices_nouvelle);
    }
    else
    {
        MatrixFinalConnexe = Matrix2;
        printf("Matrice Connexe\n");
        PrintMatrix(MatrixFinalConnexe, nbr_Vertices);
    }
    printf("aretes du graphe: %d\n", numero_aretes_graphe(MatrixFinalConnexe, nbr_Vertices_nouvelle));
    printf("degree moyen du graphe: %d\n", degree_moyen_aretes(MatrixFinalConnexe, nbr_Vertices_nouvelle));
    unsigned int sommetRandom = getsommetRandom(nbr_Vertices_nouvelle);
    unsigned int nbr_aretes_relies = Nombre_aretes_relies_a_sommet_choisie(MatrixFinalConnexe, nbr_Vertices_nouvelle, sommetRandom);
    printf("getsommetrandom: %d\n", sommetRandom);
    printf("numero_aretes_graphe: %d\n", nbr_aretes_relies);
    printf("*--------------generation sous-graphe------------*");
    array_Ty *Matrixsommets_relies = Matrix_vertices_relies(MatrixFinalConnexe, sommetRandom, nbr_aretes_relies, nbr_Vertices_nouvelle);
    Print_Matrix_File(Matrixsommets_relies, nbr_aretes_relies);
    unsigned int extra_aretes = get_nombre_des_aretes_du_Sousgraphe(MatrixFinalConnexe, Matrixsommets_relies, Matrixsommets_relies, nbr_aretes_relies);
    printf("nbr_aretes_sousgraphe_extras: %d\n", extra_aretes);
    int nbr_total_aretes_sous_graphe = extra_aretes + nbr_aretes_relies;
    printf("nbr_aretes_sousgraphe_total: %d\n", nbr_total_aretes_sous_graphe);
    printf("*--------------clique maximal------------*");
    printf("\nclique maximal du sousgraphe= %d", calculerCliqueMaximal(nbr_aretes_relies));




















































    /*Génerer un graphe*/
    //int* matrice =initGraphe();

    /*Initialisation de l'arbitre*/
    //pArbitre=initArbitre(matrice);

    /*initialisation du nembre des Couleur, trouver un nombre de coloration propre par heursitique*/
    //initNbrColoration();

    /*Initialisation des vecteurStochastique*/
    //initVecteurStochastique();

    /*calculer la taille de clique maximale de chaque sommet*/
    //calculercliqueMax();

    /*calculer la taille de clique maximale de chaque sommet*/
    //calculerArret();

    /*commence du jeu*/
    //commenceDuJeu();

    /*Imprimer tout la stucture Arbitre*/
    //printArbitre();

    /*free les mémoires*/
    //freeAll();

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