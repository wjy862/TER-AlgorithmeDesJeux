#include "../inc/sommet.h"

int alea(double p)
{

    double tmp = (double)rand()/(double)RAND_MAX;
    return tmp<=p;//si tmp<= p renvoie 1 sinon 0
}

void genererUnGraphe(int **matrice,int m,int d)
{
    int tmp = 0;
    for(int i =0; i< m ;i++)//genere graphe
    {
        for(int j=i; j<m;j++)
        {
            if(i == j)
            {
                matrice[i][j] = 0;                
            }
            else
            {
                tmp= alea((double)((double)d/(double)(m-(i+1))));
                matrice[i][j] = tmp;//m = 50 et i = 0 alors proba = d/49 ;(50 - (0+1))                 
                matrice[j][i] = matrice[i][j]; //si i+1 = m division par 0 mais si i = m-1 alors i = j donc ca "n'arrive pas"

            }
        }
    }
}
int trouverUnSousGraphe(int** matrice,int cpt,int m,int x,int* visiter,int max,int* final)
{
    //visiter[x] =1;
    int* tmp = malloc(m*sizeof(int));//creer tmp; prends les ajouts de ce sommet
    for(int i = 0;i<m;i++)
    {
        tmp[i] =0;
    }
    for(int i = 0;i<m;i++)
    {

        if(matrice[x][i] && visiter[i] == 0)//si voisin pas visité
        {
            visiter[i] = 1;//il est visité
            tmp[i] = 1;//il est visité par ce sommet
            cpt++;
            //printf("je vais visiter: %d\n",i+1);
            max = trouverUnSousGraphe(matrice,cpt,m,i,visiter,max,final);//on parcours le voisin
        }
    }
    //printf("\n");
    if(cpt>max)//fin de ligne et si plus grand sous graphe
    {
        max = cpt;
        for(int j =0;j<m;j++)//final = visiter
        {
            final[j] = visiter[j];
        }        
    }
    else
    {
        for(int j =0;j<m;j++)//ce qu'on a visité n'est plus visité
        {
            //printf("%d\t",tmp[j]);
            if(tmp[j] == 1)
            visiter[j] =0;
        }
        //printf("\n");
    }
    free(tmp);
    return max;
}

Arbitre genererUnGrapheConnexe(int** matrice,int m,int* visiter,int* final,int* cpt)
{
    int vrai_max =0;
    int nul;
    int* tmp = malloc(m*sizeof(int)); 
            //printf("jouj\n");
    for(int i=0;i<m;i++)
    {
        //if(vrai_max == m) break;//graphe connexe

        //if((m-i)>=vrai_max)//pas assez de sommet pour battre le max?(j'en suis pas sur du tout)
        //{
            nul = trouverUnSousGraphe(matrice,1,m,i,visiter,0,final);
        //}
        if(nul>vrai_max)
        {
            vrai_max = nul;
            *cpt = 0;
            for(int j = 0;j<m;j++)
            {
                tmp[j] = final[j];
                if(final[j]) *cpt = *cpt +1;
            }
        }
    }
    Arbitre ret;
    ret.listeSommet = malloc(*cpt*sizeof(Sommet));
    ret.matrice = malloc(*cpt*sizeof(int*));
    {
        for(int i =0;i<*cpt;i++)
        {
            ret.matrice[i] = malloc(*cpt*sizeof(int));
            for(int j =0;j<*cpt;j++)
            {
                ret.matrice[i][j]=0;
            }
        }
    }
    int compteur_i = 0;
    int compteur_j = 0;
    for(int i =0;i<m;i++)
    {
        if(tmp[i])
        {
            for(int j=0;j<m;j++)
            {
                if(tmp[j])
                {
                    ret.matrice[compteur_i][compteur_j] = matrice[i][j];
                    compteur_j++;
                }
            }
            compteur_i++;
            compteur_j = 0;
        }
    }

    free(tmp);
    return ret;
}

int** getSousGraphe(Arbitre arb,int index,int size,int* taille)
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
        if(arb.matrice[index][i] == 1)
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
                if(arb.matrice[i][j] ==1)
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

int main()
{
    int sommet = 10;
    int degre = 3;
    int size = 0;
    int ** adjacence = malloc(sommet* sizeof(int*));
    for(int i = 0;i<sommet;i++)
    {
        adjacence[i] = malloc(sommet* sizeof(int));
        for(int j =0;j<sommet;j++)
        {
            adjacence[i][j] =0;
        }
    }
    genererUnGraphe(adjacence,sommet,degre);
    int* visiter = malloc(sommet*sizeof(int));

    int* final = malloc(sommet*sizeof(int));

    for(int i = 0;i<sommet;i++)
    {
        visiter[i] = 0;
        final[i] = 0;
    }
    Arbitre res = genererUnGrapheConnexe(adjacence,sommet,visiter,final,&size);
    int** sousgraphe = NULL;
    int taille = 0;
    sousgraphe = getSousGraphe(res,9,size,&taille);  
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            printf("%d ",res.matrice[i][j]);
        }
        printf("\n");
    }
    printf("sous graphe:\n");
    for(int i=0;i<taille;i++)
    {
        for(int j=0;j<taille;j++)
        {
            printf("%d ",sousgraphe[i][j]);
        }
        printf("\n");
    }
    printf("\n");





    for(int i = 0;i<sommet;i++)
    {
        free(adjacence[i]);
    }

    for(int i=0;i<taille;i++)
    {
        free(sousgraphe[i]);
    }
        free(sousgraphe);
    for(int i = 0;i<size;i++)
    {
        free(res.matrice[i]);
    }
    free(adjacence);
    free(res.listeSommet);
    free(res.matrice);
    free(visiter);
    free(final);
    return 0;
}