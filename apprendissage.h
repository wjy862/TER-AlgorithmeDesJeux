
#define N 10000//itération
#define THETA 0.1//Learning rate parameter, 0<THETA<1
#define THRESHOULD 0.999//Seuil de probabilité à atteindre
double r;//Number of actions
int a;//this action
double *p;//Probability vector,[p[0],p[1]...p[r]]
double utilite;//Environmental response (P,Q,S)-> utilité

printR(double r){
    printf("Number of actions: %lf\n",r);
}
printA(double a){
    printf("this action: %lf\n",a);
}
printP(double p){
    printf("Probability vector: %lf\n",p);
}
printUtilite(double utilite){
    printf("Environmental response (P,Q,S): %lf\n",utilite);
}
void printProbabilite(Sommet pSommet,int index){
    printf("pour sommet %d, la couleur %d a une proba de: %lf\n",pSommet->index,index,pSommet->vecteurStochastique[index]);
}
double calculerUtilite(Sommet pSommet){
    double benefice=pSommet->benefice;
    double maxBenefice=pSommet->maxBenefice;
    double minBenefice=pSommet->minBenefice;
    return 1.0-((maxBenefice-benefice)/(maxBenefice-minBenefice));
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
    p[a]=p[a]+THETA*utilite*(1-p[a]);//mettre à jour proba de couleur actual
    printProbabilite(pSommet,a);
    for (int i = 0; i < r; i++) {
        if(i==a) continue;
        p[i]=p[i]-THETA*utilite*p[i];//mettre à jour les autres proba
        printProbabilite(pSommet,i);
    }
    printf("\n");
    return p[a]>=THRESHOULD?1:0;//return 1, si P>0.999
}
int linearRewardPenalty(Sommet pSommet){
    if(isthreshould(pSommet)==1) return 1;
    init(pSommet);
    p[a]=p[a]-THETA*(1-utilite)*p[a]+THETA*utilite*(1-p[a]);
    printProbabilite(pSommet,a);
    for (int i = 0; i < r; i++) {
        if(i==a) continue;
        p[i]=p[i]+THETA*(1-utilite)*((1.0/(r-1.0))-p[a])-THETA*utilite*p[i];
        printProbabilite(pSommet,i);
    }
    printf("\n");
    return p[a]>=THRESHOULD?1:0;
}
int apprendissage(Sommet pSommet){
    return linearRewardInaction(pSommet);
}
int updateVecteurStochastique(){
    printf("\nBeginning of updateVecteurStochastique\n");
    int count=0;
    for (int i = 0; i < tailleSommet; i++) {
        if(apprendissage(pArbitre->listeSommet[i])==1) count++;
    }
    printf("\nEnd of updateVecteurStochastique\n");
    return count==tailleSommet?1:0;
}