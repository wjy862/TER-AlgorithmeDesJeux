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
    matriceRepartitionCouleurConflit= malloc(tailleSommet*tailleArret*sizeof(int));
    int maxTailleSommet=tailleSommet;
    for (int nbrSommet = 3; nbrSommet <= maxTailleSommet; nbrSommet++) {/*générer des graphes de 3 sommets à 20 sommets*/
        for (int count = 0; count < TIMES; count++) { /*répéter TIMES fois le jeu à trouver equilibre de nash*/
            commenceDuJeu(nbrSommet,count);
        }
        /*nbr des fois obtenus de la coloration propre pour TIMES fois du jeu et sa répartition*/
        printNbrCouleursEtNbrConflits();
        printNbrColorationPropre(tailleSommet,(double)nbrColorationPropre/(double)TIMES);
    }
    free(matriceRepartitionCouleurConflit);
    return 0;
}

