#include "parametre.h" //les variable globale
#include "prints.h"    //prints
#include "sommet.h"
#include "graphe.h"
#include "benefice.h"
#include "apprendissage.h"
#include "jeu.h"

/*int nbrSommet: nbr sommets dans l'ensembre des graphes
 *int count: N ième tour du jeu
 * */


int main() {
    matriceRepartitionCouleurConflit= malloc((maxTailleSommet+1)*maxTailleSommet*sizeof(int));
    for (; minTailleSommet <= maxTailleSommet; minTailleSommet++) {/*générer des graphes de minTailleSommet sommets à maxTailleSommet sommets*/
        int *matrice =initParametres(minTailleSommet);
        for (int count = 0; count < TIMES; count++) { /*répéter TIMES fois le jeu à trouver equilibre de nash*/
            commenceDuJeu(matrice,minTailleSommet,count);
        }
        /*nbr des fois obtenus de la coloration propre pour TIMES fois du jeu et sa répartition*/
        printNbrCouleursEtNbrConflits();
        printNbrColorationPropre(tailleSommet,(double)nbrColorationPropre/(double)TIMES);
    }
    free(matriceRepartitionCouleurConflit);
    return 0;
}

