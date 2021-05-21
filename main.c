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
    //FILE *F3;
    //F3 = fopen("logs.data","a+");
    for (; minDegre <= maxDegre; minDegre++) {/*générer des graphes de minDegre sommets à maxDegre sommets*/
        matriceRepartitionCouleurConflit= malloc((maxTailleSommet+1)*(((maxTailleSommet-1)*(maxTailleSommet))/2)*sizeof(int));//maxNbrCouleur*maxConflitTotal
        if(minTailleSommet<minDegre) minTailleSommet=minDegre;
        for (; minTailleSommet <= maxTailleSommet; minTailleSommet++) {/*générer des graphes de minTailleSommet sommets à maxTailleSommet sommets*/
            int *matrice =initParametres(minTailleSommet);
            for (int count = 1; count <=TIMES; count++) { /*répéter TIMES fois le jeu à trouver equilibre de nash*/
                commenceDuJeu(matrice,count);
            }
            /*nbr des fois obtenus de la coloration propre pour TIMES fois du jeu et sa répartition*/
            printMatice(tailleSommet,tailleArret,pArbitre->matrice);
            printNbrCouleursEtNbrConflits();
            printNbrColorationPropre(tailleSommet,(double)nbrColorationPropre/(double)TIMES);
            free(matrice);
        }
    free(matriceRepartitionCouleurConflit);
    }
    //fclose(F3);
    return 0;
}

