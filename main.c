#include "inc/parametre.h" //les variable globale
#include "inc/prints.h"    //prints
#include "inc/sommet.h"
#include "inc/graphe.h"
#include "inc/benefice.h"
#include "inc/apprentissage.h"
#include "inc/jeu.h"
#include "inc/parametre.h"
#include "inc/struct.h"

/*int nbrSommet: nbr sommets dans l'ensembre des graphes
 *int count: N ième tour du jeu
 * */
/*
int graphe1[maxTailleSommet][maxTailleSommet]=
        {{0,1,0,1,0,1},
         {1,0,1,0,1,0},
         {0,1,0,1,0,1},
         {1,0,1,0,1,0},
         {0,1,0,1,0,1},
         {1,0,1,0,1,0}};

int graphe2[maxTailleSommet][maxTailleSommet]=
        {{0,1,0,1,0,1,0},
         {1,0,1,0,1,0,0},
         {0,1,0,1,0,1,0},
         {1,0,1,0,1,0,0},
         {0,1,0,1,0,1,1},
         {1,0,1,0,1,0,1},
         {0,0,0,0,1,1,0}};

int graphe3[maxTailleSommet][maxTailleSommet]=
        {{0,0,0,1,0,1,0,0,0,0},
         {0,0,1,0,1,0,0,0,0,0},
         {0,1,0,0,0,1,0,1,0,0},
         {1,0,0,0,1,0,0,0,0,0},
         {0,1,0,1,0,0,0,1,0,1},
         {1,0,1,0,0,0,1,0,1,0},
         {0,0,0,0,0,1,0,0,0,1},
         {0,0,1,0,1,0,0,0,1,0},
         {0,0,0,0,0,1,0,1,0,1},
         {0,0,0,0,1,0,1,0,1,0}};

int graphe4[maxTailleSommet][maxTailleSommet]=
        {{0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
         {0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
         {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
         {0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
         {1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
         {0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
         {0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0},
         {0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1},
         {0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
         {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0}};

int graphe5[maxTailleSommet][maxTailleSommet]=
        {{0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
         {0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
         {0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
         {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
         {0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
         {1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
         {0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
         {1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0},
         {0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1},
         {0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
         {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0}};
int graphe6[maxTailleSommet][maxTailleSommet]=
        {{0,1,1,1,0,1},
         {1,0,0,1,0,1},
         {1,0,0,1,1,0},
         {1,1,1,0,1,0},
         {0,0,1,1,0,1},
         {1,1,0,0,1,0}};*/
int minTailleSommet=6;//minTailleSommet est la minimum nb sommet qu'on peut avoir dans le graphe
int minDegre=6;
int maxDegre=6;


Arbitre pArbitre;
int couleurHeuristique;
double nbrCouleur;//Nombre total des couleurs dans la graphe
double nbStrategies;//(double) couleurHeuristique pour calculer
int nbrColorationPropre;
int sommeConflits;
int *matriceRepartitionCouleurConflit;
int tailleSommet;//ne change pas svp, utilise minTailleSommet et maxTailleSommet pour changer nb sommet du graphe
int tailleArret;//ne change pas svp, utilise minTailleSommet et maxTailleSommet pour changer nb sommet du graphe


/*apprandissage.h*/
double r;//Number of actions
int a;//this action
double *p;//Probability vector,[p[0],p[1]...p[r]]
double utilite;//Environmental response (P,Q,S)-> utilité








int main() {

    //FILE *F3;
    //F3 = fopen("logs.data","a+");
    for (; minDegre <= maxDegre; minDegre++) {/*générer des graphes de minDegre sommets à maxDegre sommets*/
        matriceRepartitionCouleurConflit= malloc((maxTailleSommet+1)*(((maxTailleSommet-1)*(maxTailleSommet))/2)*sizeof(int));//maxNbrCouleur*maxConflitTotal
        if(minTailleSommet<minDegre) minTailleSommet=minDegre;
        for (; minTailleSommet <= maxTailleSommet; minTailleSommet++) {/*générer des graphes de minTailleSommet sommets à maxTailleSommet sommets*/
            int *matrice =initParametres(minTailleSommet,minDegre);
            for (int count = 1; count <=TIMES; count++) { /*répéter TIMES fois le jeu à trouver equilibre de nash*/
                
                commenceDuJeu(matrice,count);
            
            }

            /*nbr des fois obtenus de la coloration propre pour TIMES fois du jeu et sa répartition*/
            printMatice(tailleSommet,tailleArret,pArbitre->matrice);
            freeAll();            
            //exit(3);            
            printNbrCouleursEtNbrConflits();
            printNbrColorationPropre(tailleSommet,(double)nbrColorationPropre/(double)TIMES);
            free(matrice);
            
        }
    free(matriceRepartitionCouleurConflit);
    }
    //fclose(F3);
    return 0;
}

