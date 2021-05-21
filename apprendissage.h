#define THETA 0.1//Learning rate parameter, 0<THETA<1
double calculerUtilite(Sommet pSommet){
    double benefice=pSommet->benefice;
    double maxBenefice=pSommet->maxBenefice;
    double minBenefice=pSommet->minBenefice;
    return 1.0-((maxBenefice-benefice)/((maxBenefice-minBenefice)==0?1:(maxBenefice-minBenefice)));//denominateur ne peut etre 0
}

int isthreshould(Sommet pSommet){
    for (int i = 0; i < couleurHeuristique; i++) {
        if(pSommet->vecteurStochastique[i]>=THRESHOULD) return 1;
    }
    return 0;
}
void init(Sommet pSommet){
    //initialisation des parametres
    r= (double)couleurHeuristique;
    a=pSommet->couleur;
    p=pSommet->vecteurStochastique;
    utilite=calculerUtilite(pSommet);
}
int linearRewardInaction(Sommet pSommet){
    if(isthreshould(pSommet)==1) return 1;//return 1, si P>0.999, on ne calcul plus donc
    init(pSommet);//initialisation
    p[a]=p[a]+THETA1*utilite*(1-p[a]);//mettre à jour proba de couleur actual
    //printProbabilite(pSommet,a);
    for (int i = 0; i < r; i++) {
        if(i==a) continue;
        p[i]=p[i]-THETA1*utilite*p[i];//mettre à jour les autres proba
        //printProbabilite(pSommet,i);
    }
    //printf("\n");
    return p[a]>=THRESHOULD?1:0;//return 1, si P>0.999
}
int linearRewardPenalty(Sommet pSommet){
    if(r==1.0) return 0;//denominateur ne peut etre 0
    if(isthreshould(pSommet)==1) return 1;
    init(pSommet);
    p[a]=p[a]-THETA1*(1-utilite)*p[a]+THETA1*utilite*(1-p[a]);
    //printProbabilite(pSommet,a);
    for (int i = 0; i < r; i++) {
        if(i==a) continue;
        p[i]=p[i]+THETA1*(1-utilite)*((1.0/(r-1.0))*p[a])-THETA1*utilite*p[i];
        //printProbabilite(pSommet,i);
    }
    //printf("\n");
    return p[a]>=THRESHOULD?1:0;
}
int linearRewardPenalty2(Sommet pSommet){
    double pCumule=0;
    if(r==1.0) return 0;//denominateur ne peut etre 0
    if(isthreshould(pSommet)==1) return 1;
    init(pSommet);
    p[a]=p[a]-THETA2*(1-utilite)*p[a]+THETA1*utilite*(1-p[a]);
    //printProbabilite(pSommet,a);
    for (int i = 0; i < r; i++) {
        if(i==a) continue;
        p[i]=p[i]+THETA2*(1-utilite)*((1.0/(r-1.0))*p[a])-THETA1*utilite*p[i];
        pCumule+=p[i];
        //printProbabilite(pSommet,i);
    }
    if(p[a]!=1-pCumule) p[a]=1-pCumule;
    //printf("\n");
    return p[a]>=THRESHOULD?1:0;
}
int apprendissage(Sommet pSommet){
    return METHODE(pSommet);
    //return linearRewardInaction(pSommet);
    //return linearRewardPenalty(pSommet);
    //return linearRewardPenalty2(pSommet);

}
int updateVecteurStochastique(){
    //printf("\nBeginning of updateVecteurStochastique\n");
    int count=0;
    for (int i = 0; i < tailleSommet; i++) {
        if(apprendissage(pArbitre->listeSommet[i])==1) count++;
    }
    //printf("\nEnd of updateVecteurStochastique\n");
    return count==tailleSommet?1:0;
}