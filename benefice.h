#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void setBenefice(Sommet pSommet){
    //pSommet->benefice=benefice()
}
void calculerBenefice(Arbitre pArbitre){
    printf("beginning of calculerBenefice\n");
    for (int i = 0; i < pArbitre->tailleSommet; ++i) {
        setBenefice(pArbitre->listeSommet[i]);
    }
    printf("end of calculerBenefice\n");
}