#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void setBenefice(Sommet pSommet,Arbitre pArbitre){
    //pSommet->benefice=getbenefice();
}
void calculerBenefice(Arbitre pArbitre){
    printf("\nbeginning of calculerBenefice\n");
    for (int i = 0; i < pArbitre->tailleSommet; ++i) {
        setBenefice(pArbitre->listeSommet[i],pArbitre);
    }
    printf("end of calculerBenefice\n\n");
}