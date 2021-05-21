

/*nbr conflits totals dans l'ensembre du graphe*/
int calculerSommeConflits(){
    int count=0;
    for (int i = 0; i < tailleSommet; i++) {
        count+=pArbitre->listeSommet[i]->nbrConflits;
    }
    sommeConflits=count/2;//En fait, chaque conflit a été calculé deux fois(conflits entre deux sommets), je pense c'est plus jolie d'afficher qu'une fois..
    return sommeConflits;
}
void calculerNbrColorationPropre(int times){
    if(calculerSommeConflits()==0) nbrColorationPropre++;
    /*printf("%dst game starts\n",times);
    printf("somme du nombre des Conflits: %d\n",sommeConflits/2);
    printf("nombre total des Couleur: %d\n\n",(int)nbrCouleur);
    printf("%dst game ends\n",times);*/
}


double calculerNbrCouleurTotal(){
    int *listCouleurs=malloc(tailleSommet*sizeof(int));//chaque index présente une couleur
    int count=0;
    for (int k = 0; k < tailleSommet; k++) {
        listCouleurs[k]=0;//initialiser
    }
    for (int i = 0; i < tailleSommet; i++) {
        listCouleurs[pArbitre->listeSommet[i]->couleur]++;//Si un sommet est coloriée par couleur 0 -> listCouleurs[0]++
    }

    for (int j = 0; j < tailleSommet; j++) {
        //printf("Couleur %d est utilisé %d fois\n",j,listCouleurs[j]);
        if(listCouleurs[j]!=0) count++;//counter ce qui n'est pas 0 dans la list Couleurs
    }
    free(listCouleurs);
    nbrCouleur=(double)count;
    //printf("Nombre total des couleurs dans la graphe: %lf\n",nbrCouleur);
    return nbrCouleur;
}


//initialisation
void initVecteurStochastique(){
    for (int index = 0; index < tailleArret; index++) {
        pArbitre->listeSommet[index]->vecteurStochastique = malloc(couleurHeuristique * sizeof(double));
        for (int k = 0; k < couleurHeuristique; k++) {
            pArbitre->listeSommet[index]->vecteurStochastique[k] = (1.0 / couleurHeuristique);
        }
        //printVecteurStochastique(pArbitre->listeSommet[index]);
    }
}
void initSommet(int index,Sommet listeSommet[]){
    Sommet pSommet;
    pSommet=malloc(sizeof(struct Sommet));
    if (!pSommet) exit(1);
    //printf("\nBeginning of vertex%d initialisation\n",index);
    pSommet->index=index;
    pSommet->couleur=-1;
    pSommet->nbrConflits=-1;
    pSommet->benefice=0.0;
    pSommet->maxBenefice=0.0;
    pSommet->minBenefice=0.0;
    pSommet->cliqueMax=-1;
    pSommet->nbrArrets=-1;
    pSommet->coul_ss_graph = 0;
    listeSommet[index]=pSommet;
    //printSommet(pSommet);
    //printf("Vertex initialisation succeed\n\n");
}
Arbitre initArbitre(int (*matrice)[tailleSommet]){
    //printf("Beginning of Arbitre initialisation\n");
    Arbitre pArbitre;
    pArbitre=malloc(2*sizeof(int)+sizeof(int*)+sizeof(Sommet*));
    pArbitre->listeSommet=malloc(tailleSommet*sizeof(Sommet));
    if (!pArbitre||!pArbitre->listeSommet) exit(1);
    pArbitre->tailleSommet=tailleSommet;
    pArbitre->tailleArret=tailleArret;
    pArbitre->matrice=matrice[0];
    for (int i = 0; i < pArbitre->tailleSommet; i++) {
        initSommet(i,pArbitre->listeSommet);
    }
    //printf("Arbitre initialisation succeed\n\n");
    return pArbitre;
}
//colorier
double unif() {
    static unsigned int seed = 0;
    seed++;
    srand((unsigned) time(NULL) + seed * seed);
    return (double)random()/((double)RAND_MAX);
}
int getCouleur(Sommet pSommet){
    /*la probalibité pour une stratégie*/
    double *p= pSommet->vecteurStochastique;
    /*la probalilité cumulée*/
    double cumuleeP=0.0;
    double thisP=unif();
    //printf("Génerer un p suite de la loi uniforme, thisP: %lf\n", thisP);
    for (int k = 0; k < couleurHeuristique; k++) {
        cumuleeP+=*(p+k);
        //printf("P%d: %lf\n",k, cumuleeP);
        if(thisP<cumuleeP) {
            //printf("k: %d\n", k);
            pSommet->couleur=k;
            //printf("Coloriser Sommet %d par le couleur %d\n",pSommet->index,pSommet->couleur);
            //printf("\n");
            return k;
        }
    }
    //printf("cumuleeP %lf is less than this p %lf",cumuleeP,thisP);
    exit(245);
}
void colorier(){
    //printf("\nBeginning of colorier\n");
    for(int a = 0; a < pArbitre->tailleSommet; a++){
        getCouleur(pArbitre->listeSommet[a]);
    }
    //printf("End of colorier\n\n");
}
//conflit
int isConflit(Sommet unSommet,Sommet autreSommet){
    if(unSommet->couleur==autreSommet->couleur) return 1;
    return 0;
}
void calculerArret(){
    //printf("\nBeginning of calculerArret\n");
    for(int b= 0; b<pArbitre->tailleSommet; b++){
        int countArrets=0;
        for(int c= 0; c< pArbitre->tailleArret; c++){
            if(*(pArbitre->matrice+b*pArbitre->tailleArret+c)==1) {
                countArrets++;
            }
        }
        pArbitre->listeSommet[b]->nbrArrets=countArrets;
        //printIndex(pArbitre->listeSommet[b]);
        //printNbrArrets(pArbitre->listeSommet[b]);
        //printf("\n");
    }
    //printf("End of calculerArret\n\n");
}
void calculerConflit(){
    //printf("\nBeginning of calculerConflit\n");
    for(int b= 0; b<pArbitre->tailleSommet; b++){
        int countConflits=0;
        for(int c= 0; c< pArbitre->tailleArret; c++){
            if(*(pArbitre->matrice+b*pArbitre->tailleArret+c)==1) {
                countConflits+=isConflit(pArbitre->listeSommet[b],pArbitre->listeSommet[c]);
            }
        }
        pArbitre->listeSommet[b]->nbrConflits=countConflits;
        //printIndex(pArbitre->listeSommet[b]);
        //printNbrConflits(pArbitre->listeSommet[b]);
        //printf("\n");
    }
    //printf("End of calculerConflit\n\n");
}
//calculer la taille Clique Maximale
int** getSousGrapheClique(Arbitre arb,int index,int size,int* taille)
{
    if(index >= size)
    {
        printf("l'index ne correspond à aucun sommet\n");
        return NULL;
    }
    int cpt = 1;
    int cpt_i = 0;
    int cpt_j = 0;
    int* tmp = malloc(size*sizeof(int));
    int **ret;
    for(int i=0;i<size;i++)
    {
        tmp[i] =0;
    }
    for(int i=0;i<size;i++)
    {
        //printf("%d ",arb.matrice[index][i]);
       // if(arb.matrice[index][i] == 1)
        if(*(arb->matrice+index*size+i) == 1)

        {
            tmp[i]=1;//on ajoute les voisins du sommet index
            cpt++;
        }
    }
    //printf("cpt sous graphe = %d\n",cpt);
    ret = malloc(cpt*sizeof(int*));
    for(int i =0;i<cpt;i++)
    {
        ret[i] = malloc(cpt*sizeof(int));
        for(int j =0;j<cpt;j++)
        {
            ret[i][j] = 0;
        }
    }
    for(int i = 1;i<cpt;i++)
    {
        ret[0][i]= 1;
        ret[i][0] =1;
    }
    *taille = cpt;
    cpt_i = 1;
    cpt_j = 0;
    for(int i =0;i<size;i++)//on cherche les voisins du sommet index
    {
        if(tmp[i] == 0) continue;//pas un sommet du sous graphe
        //printf("%d\t",i+1);
        for(int j=0;j<size;j++)
        {
            if(tmp[j])//pas un sommet du sous graphe|| se regarde lui même
            {
                cpt_j ++;//tmp vaut 1 donc on incrémente cpt_j
                //if(arb.matrice[i][j] ==1)
                if(*(arb->matrice+i*size+j) ==1)
                {
                    //printf("i:%d j:%d\n",i+1,j+1);
                    ret[cpt_i][cpt_j] = 1;
                }
            }
        }
        cpt_i++;
        cpt_j = 0;
    }
    free(tmp);
    return ret;
}


int diminuer(int* binaire, int taille,int i)
{
    int cpt = 0;
        if(i == taille-1 && binaire[i]==0)//?
        {
            return 0;
        }
        if(binaire[i] == 1)
        {
            binaire[i]=0;
            while(i != 0)
            {
                binaire[i-1] = 1;
                i--;
            }
            for(int i=0;i<taille;i++)
            {
                if(binaire[i] == 1)
                {
                    cpt++;
                }
            }
            //printf("##cpt = %d##\n",cpt);
            return cpt;
        }
        else
        {
            return diminuer(binaire,taille,i+1);
        }
}

int calculerCliqueMaximale(Arbitre arb,int f){
    //printf("What\n");
    int** tmp;
    int ret = 0;
    int fin =1;
    int faux =0;
    int taille = 0;
    int* binaire;

    tmp = getSousGrapheClique(arb,f,arb->tailleSommet,&taille);
    ret = 0;
    binaire = malloc(taille*sizeof(int));
    //printf("taille vaut %d\n",taille);
    for(int j = 0;j<taille;j++)
    {
        binaire[j] = 1;
    }
    while(fin !=0)
    {
        for(int i =0;i<taille-1 && faux == 0;i++)
        {
            if(binaire[i] == 0) continue;
            for(int j =i+1;j<taille && faux == 0;j++)
            {
                if(binaire[j]==0)continue;
                if(tmp[i][j]==0) faux = 1;
            }
        }
        if(!faux)//clique trouvée?
        {
            if(fin > ret) ret = fin;
        }
            //printf("fin vaut:%d\n",fin);
            fin = diminuer(binaire,taille,0);
            //printf("fin vaut:%d\n",fin);
            /*printf("###bin vaut:");
            for(int i =0;i<taille;i++)
            {
                printf("%d ",binaire[i]);
            }
            printf("\n");*/
            faux =0;
    }
        for(int i =0;i<taille;i++)
    {
        free(tmp[i]);
    }
    free(tmp);
    free(binaire);
    //printf("### clique_max = %d ###\n",ret);
    return ret;
    //return 3;
}
void calculercliqueMax(){
    for (int i = 0; i < tailleArret; i++) {
        pArbitre->listeSommet[i]->cliqueMax=calculerCliqueMaximale(pArbitre,i);
    }
}

//nombre de couleurs d'un sous graphe
int calculerNbrCouleurLocal(Arbitre arb,int index)
{
    int cpt= 1;

    int * nb_coul = malloc((int)nbrCouleur*sizeof(int));
    for(int i=0;i<(int)nbrCouleur;i++)
    {
        nb_coul[i] = 0;

    }
    for(int i =0;i<tailleSommet;i++)
    {

        if(isVoisin(index,i) && nb_coul[arb->listeSommet[i]->couleur] ==0)
        {
            //printf("%d est voisin avec %d\n",index,i);
            nb_coul[arb->listeSommet[i]->couleur] =1;
            cpt++;
        }
    }
    free(nb_coul);
    return cpt;
}

void calculerCouleurSsgraphe(){
    for (int i = 0; i < tailleArret; i++) {
        pArbitre->listeSommet[i]->coul_ss_graph=calculerNbrCouleurLocal(pArbitre,i);
        }
}
//heuristiqueColoration
int isVoisin(int ligne,int colonne){
    //printf("*(pArbitre->matrice+ligne*tailleArret+colonne): %d\n",*(pArbitre->matrice+ligne*tailleArret+colonne));
    return (*(pArbitre->matrice+ligne*tailleArret+colonne))==1;
}
/*0 si il existe dans la liste
 *1 si il n'existe pas dans las liste
 * */
int isDefferentFromAnyElements(int index,int *list,int taille){
    for (int k = 0; k < taille; k++) {
        if(list[k]==index) return 0;
    }
    return 1;
}
int findNbrVoisinNonColorie(int index,int *sommetsColorie,int tailleSommetsColorie){
    int count=0;
    for (int voisin = 0; voisin < tailleArret; voisin++) {//index arret
        if(isVoisin(index,voisin)){
            count+=isDefferentFromAnyElements(voisin,sommetsColorie,tailleSommetsColorie);
        }
    }
    //printf("Chercher un voisin moins contraint, voisin: Sommet %d dont %d voisins non colorié\n",index,count);
    return count;
}

int getProchainVoisinLeMoinsContraint(int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie,int tailleVoisinNonColorie){
    //print la structure des parametre
    //printTailleSommetsColorie(tailleSommetsColorie);
    //printTailleVoisinNonColorie(tailleVoisinNonColorie);
    //printSommetsColorie(sommetsColorie,tailleSommetsColorie);
    //printVoisinsNonColorie(voisinsNonColorie,tailleVoisinNonColorie);

    int index;//index de sommet
    int max=RAND_MAX;//nombre de voisin non colorie
    for (int i = 0; i < tailleVoisinNonColorie; i++) {//index voisin
       int count=findNbrVoisinNonColorie(voisinsNonColorie[i],sommetsColorie,tailleSommetsColorie);
        if(count<max){
            max=count;
            index=voisinsNonColorie[i];
        }else if(count=max){
            index=unif()<0.5?index:voisinsNonColorie[i];
        }
    }
    return index;
}
void heuristiqueColorier(int index,int *sommetsColorie,int tailleSommetsColorie){
    int *listecouleur= malloc(tailleArret* sizeof(int));
    for (int t = 0; t < tailleSommet; t++) {
        listecouleur[t]=0;
    }
    for (int voisin = 0; voisin < tailleArret; voisin++) {
        if(isVoisin(index,voisin)){
            if(isDefferentFromAnyElements(voisin,sommetsColorie,tailleSommetsColorie)==0){
                listecouleur[pArbitre->listeSommet[voisin]->couleur]++;
            }
        }
    }
    for (int i = 0; i < tailleArret; i++) {
       if(listecouleur[i]==0){
           pArbitre->listeSommet[index]->couleur=i;
           //printf("Sommet %d est le voisin moins contraint, colorié par couleur: %d\n\n",pArbitre->listeSommet[index]->index,i);
           break;
       }
    }
    free(listecouleur);
}
int* trouverListeVoisin(int *sommetsColorie,int tailleSommetsColorie){
    /*si trouver un voisin liste[voisin]++,eliminer les sommets Colorie à la fin*/
    int *listeVoisin=malloc(tailleArret* sizeof(int));
    for (int t = 0; t < tailleSommet; t++) {
        listeVoisin[t]=0;
    }
    for (int index = 0; index < tailleSommetsColorie; index++) {
        for (int voisin = 0; voisin < tailleArret; voisin++) {
            if(isVoisin(sommetsColorie[index],voisin)) {
                listeVoisin[voisin]++;
                //printf("sommet %d sont voisin de sommet %d\n",index,voisin);
            }else{
                //printf("sommet %d ne sont pas voisin de sommet %d\n",index,voisin);
            }
        }
    }
    for (int index = 0; index < tailleSommetsColorie; index++) {
        listeVoisin[sommetsColorie[index]]=0;
        //printf("sommet %d ont colorié\n", sommetsColorie[index]);
    }
    return listeVoisin;
}
int calculerTailleVoisinNonColorie(int *sommetsColorie,int tailleSommetsColorie){
    int count=0;
    int *listeVoisin= trouverListeVoisin(sommetsColorie,tailleSommetsColorie);
    for (int t = 0; t < tailleArret; t++) {
        if(listeVoisin[t]!=0) count++;
    }
    free(listeVoisin);
    return count;
}
int* calculerVoisinsNonColorie(int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie){
    int count=0;
    int *listeVoisin= trouverListeVoisin(sommetsColorie,tailleSommetsColorie);
    for (int t = 0; t < tailleSommet; t++) {
        voisinsNonColorie[t]=0;
        if(listeVoisin[t]!=0) voisinsNonColorie[count++]=t;
    }
    free(listeVoisin);
    return voisinsNonColorie;
}
int heuristiqueColoriser(int count,int *sommetsColorie,int tailleSommetsColorie,int *voisinsNonColorie,int tailleVoisinNonColorie){
    if(count==0) return count;
    //printf("\nA tour %d,il reste %d sommets non colorié\n",tailleSommet-count,count);
    int voisin=getProchainVoisinLeMoinsContraint(sommetsColorie,tailleSommetsColorie,voisinsNonColorie,tailleVoisinNonColorie);
    heuristiqueColorier(voisin,sommetsColorie,tailleSommetsColorie);
    tailleSommetsColorie++;
    sommetsColorie[tailleSommetsColorie-1]=voisin;
    tailleVoisinNonColorie=calculerTailleVoisinNonColorie(sommetsColorie,tailleSommetsColorie);
    voisinsNonColorie=calculerVoisinsNonColorie(sommetsColorie,tailleSommetsColorie,voisinsNonColorie);
    count--;
    count=heuristiqueColoriser(count,sommetsColorie,tailleSommetsColorie,voisinsNonColorie,tailleVoisinNonColorie);
    return count;
}

int initNbrColoration(){
    //printf("\nBeginning of heuristiqueColoration\n");
    int couleurmax=0;
    int count=tailleArret;
    //choisir un sommet par hasard puis colorier
    int indexPremierSommet=(int)(unif()*tailleSommet);
    //printf("Sommet %d est la premier sommet colorié par couleur: %d\n",indexPremierSommet,0);
    pArbitre->listeSommet[indexPremierSommet]->couleur=0;
    count--;
    //création des parametres
    int tailleSommetsColorie,tailleVoisinNonColorie;
    int *sommetsColorie= malloc(tailleArret* sizeof(int));
    int *voisinsNonColorie= malloc(tailleArret* sizeof(int));
    for (int i = 0; i < tailleSommet; i++) {
        sommetsColorie[i]=0;
        voisinsNonColorie[i]=0;
    }
    //initialisation des parametres
    sommetsColorie[0]=indexPremierSommet;
    tailleSommetsColorie=1;
    tailleVoisinNonColorie= calculerTailleVoisinNonColorie(sommetsColorie,tailleSommetsColorie);
    voisinsNonColorie=calculerVoisinsNonColorie(sommetsColorie,tailleSommetsColorie,voisinsNonColorie);
    //print la structure des parametre
    //printTailleSommetsColorie(tailleSommetsColorie);
    //printTailleVoisinNonColorie(tailleVoisinNonColorie);
    //printSommetsColorie(sommetsColorie,tailleSommetsColorie);
    //printVoisinsNonColorie(voisinsNonColorie,tailleVoisinNonColorie);
    //colorier les voisin
    heuristiqueColoriser(count,sommetsColorie,tailleSommetsColorie,voisinsNonColorie,tailleVoisinNonColorie);
    //calculer Nbr Couleur Total
    couleurHeuristique=(int)calculerNbrCouleurTotal();
    //remettre les valeur
    for (int i = 0; i < tailleSommet; i++) {
        pArbitre->listeSommet[i]->couleur=-1;
    }
    //free les memoires
    free(sommetsColorie);
    free(voisinsNonColorie);
    //printf("\nEnd of heuristiqueColoration\n");
    return couleurHeuristique;
}
/*calculer Minimal Coloration Propre parmi les 1000 fois*/
int calculerMinColorationPropre(){
    int min=RAND_MAX;
    printf("Nombre de couleur total: %d\n",couleurHeuristique);
    for (int k = 1; k < couleurHeuristique+1; k++) {
        for (int m = 0; m < (((maxTailleSommet-1)*(maxTailleSommet))/2); m++) {
            if((*(matriceRepartitionCouleurConflit+k*(((maxTailleSommet-1)*(maxTailleSommet))/2)+m))!=0 && m==0 && k<min) min=k;//l'index le plus petit à la prémière ligne
        }
    }
    return min;
}
/*calculer la distribution des couleurs/conflits parmi les 1000 fois*/
void calculerNbrCouleursEtNbrConflits() {
    (*(matriceRepartitionCouleurConflit + (int) nbrCouleur * (((maxTailleSommet-1)*(maxTailleSommet))/2) + sommeConflits))++;
    //printf("(nb couleurs: %d, nb conflits: %d) \n", (int) nbrCouleur, sommeConflits);

}









































