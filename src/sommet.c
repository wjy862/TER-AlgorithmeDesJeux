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
            ret.matrice[i] = malloc(m*sizeof(int));
            for(int j =0;j<m;j++)
            {
                ret.matrice[i][j]=0;
            }
        }
    }
    int compteur = 0;
    for(int i =0;i<m;i++)
    {
        if(tmp[i])
        {
            for(int j=0;j<m;j++)
            {
                ret.matrice[compteur][j] = matrice[i][j];
            }
            compteur++;
        }
    }
    //printf("\n");
    free(tmp);
    return ret;
}


int main()
{
    int sommet = 25;
    int cpt = 0;
    int ** adjacence = malloc(sommet* sizeof(int*));
    for(int i = 0;i<sommet;i++)
    {
        adjacence[i] = malloc(sommet* sizeof(int));
        for(int j =0;j<sommet;j++)
        {
            adjacence[i][j] =0;
        }
    }
    genererUnGraphe(adjacence,sommet,1);
    int* visiter = malloc(sommet*sizeof(int));

    int* final = malloc(sommet*sizeof(int));

    for(int i = 0;i<sommet;i++)
    {
        visiter[i] = 0;
        final[i] = 0;
    }
    Arbitre res = genererUnGrapheConnexe(adjacence,sommet,visiter,final,&cpt);
    for(int i=0;i<13;i++)
    {
        for(int j=0;j<sommet;j++)
        {
            printf("%d ",res.matrice[i][j]);
        }
        printf("\n");
    }
    /*for(int i=0;i<sommet;i++)
    {
        for(int j=0;j<sommet;j++)
        {
            printf("%d ",test.matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/





    for(int i = 0;i<sommet;i++)
    {
        free(adjacence[i]);
    }

    for(int i = 0;i<cpt;i++)
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