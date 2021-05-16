/*
int alea(double p);
void genererUnGraphe(int **matrice,int m,int d);
int trouverUnSousGraphe(int** matrice,int cpt,int m,int x,int* visiter,int max,int* final);
struct Arbitre genererUnGrapheConnexe(int** matrice, int m, int* visiter, int* final, int* cpt);
int** getSousGraphe(A arb,int index,int size,int* taille);


int alea(double p){

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

struct Arbitre genererUnGrapheConnexe(int** matrice, int m, int* visiter, int* final, int* cpt)
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
    A ret;
    //ret.listeSommet = malloc(*cpt*sizeof(Sommet));
    //ret.matrice = malloc(*cpt*sizeof(int*));
    ret.matrice = malloc((*cpt)*(*cpt)*sizeof(int));
    {
        for(int i =0;i<*cpt;i++)
        {
            //ret.matrice[i] = malloc(*cpt*sizeof(int));
            for(int j =0;j<*cpt;j++)
            {
                //ret.matrice[i][j]=0;
                *(ret.matrice+i*(*cpt)+j)=0;
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
                    //ret.matrice[compteur_i][compteur_j] = matrice[i][j];
                    *(ret.matrice+compteur_i*m+compteur_j)= matrice[i][j];
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

int** getSousGraphe(A arb,int index,int size,int* taille)
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
        if(*(arb.matrice+index*size+i) == 1)

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
                if(*(arb.matrice+i*size+j) ==1)
                {
                    printf("i:%d j:%d\n",i+1,j+1);
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
int* initGraphe(){
    int sommet = tailleSommet;
    int degre = DEGRE;
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
    A res = genererUnGrapheConnexe(adjacence,sommet,visiter,final,&size);
    int** sousgraphe = NULL;
    int taille = 0;
    sousgraphe = getSousGraphe(res,2,size,&taille);
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            //printf("%d ",res.matrice[i][j]);
            printf("%d ",*(res.matrice+i*size+j));

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

    tailleSommet=sommet;// int tailleSommet
    tailleArret=sommet;// int tailleArret

    for(int i = 0;i<sommet;i++)
    {
        free(adjacence[i]);
    }

    for(int i=0;i<taille;i++)
    {
        free(sousgraphe[i]);
    }
    free(sousgraphe);
    free(adjacence);
    free(visiter);
    free(final);
    //free(res.matrice);
    //free(res.listeSommet);
    return res.matrice;
}
*/





#include <stdio.h>
#include <stdlib.h>

#define MAX_TOURS 9999

typedef struct array_Ty array_Ty;
struct array_Ty
{
    unsigned int sommet;
    struct list_Ty *list;
};

typedef struct list_Ty list_Ty;
struct list_Ty
{
    unsigned int valeur;
    unsigned int sommet;
    struct list_Ty *next;
};

unsigned int nbr_Vertices, nbr_Vertices_nouvelle, nbr_sommets_non_connexes;
struct list_Ty *list, *l, *l1, *l2;
int *matrice;

struct array_Ty *CreateMatrix_forcee(int size)
{
    struct array_Ty *Matrix;

    Matrix = malloc(size * sizeof(*Matrix));

    for (int i = 0; i < size; i++)
    {

        Matrix[i].sommet = i;
        Matrix[i].list = NULL;
        list = malloc(sizeof(struct list_Ty));

        for (int j = 0; j < size; j++)
        {
            if (!Matrix[i].list)
                Matrix[i].list = list;
            else
            {
                list->next = malloc(sizeof(struct list_Ty));
                list = list->next;
            }

            if (i == j || i == 1 || j == 1 || i == 3 || j == 3)
            {
                list->sommet = j;
                list->valeur = 0;
                list->next = NULL;
            }
            else
            {
                list->sommet = j;
                list->valeur = 1;
                list->next = NULL;
            }
        }
    }

    return Matrix;
}

struct array_Ty *CreateMatrix_vide(int sommets)
{
    struct array_Ty *Matrix;

    Matrix = malloc(sommets * sizeof(*Matrix));

    for (int i = 0; i < sommets; i++)
    {

        Matrix[i].sommet = i;
        Matrix[i].list = NULL;
        list = malloc(sizeof(struct list_Ty));

        for (int j = 0; j < sommets; j++)
        {

            if (!Matrix[i].list)
                Matrix[i].list = list;
            else
            {
                list->next = malloc(sizeof(struct list_Ty));
                list = list->next;
            }

            list->sommet = j;
            list->valeur = 0;
            list->next = NULL;
        }
    }

    return Matrix;
}

struct array_Ty *CreateMatrix()
{
    struct array_Ty *Matrix;

    Matrix = malloc(nbr_Vertices * sizeof(*Matrix));

    for (int i = 0; i < nbr_Vertices; i++)
    {

        Matrix[i].sommet = i;
        Matrix[i].list = NULL;
        list = malloc(sizeof(struct list_Ty));
        for (int j = 0; j < nbr_Vertices; j++)
        {
            if (j > i)
            {
                int n = rand() % 2;
                if (!Matrix[i].list)
                    Matrix[i].list = list;
                else
                {
                    list->next = malloc(sizeof(struct list_Ty));
                    list = list->next;
                }

                list->sommet = j;
                if (list->sommet == i)
                    list->valeur = 0;
                else
                {
                    list->valeur = n;
                }
                list->next = NULL;
            }
            else
            {
                if (!Matrix[i].list)
                    Matrix[i].list = list;
                else
                {
                    list->next = malloc(sizeof(struct list_Ty));
                    list = list->next;
                }
                list->sommet = j;
                if (list->sommet == i)
                    list->valeur = 0;
                else
                {
                    list->valeur = 0;
                }
                list->next = NULL;
            }
        }
    }
    return Matrix;
}

void PrintMatrix(array_Ty *matrix, int size)
{
    l = malloc(sizeof(struct list_Ty));
    int i = 0;
    while (matrix[i].sommet < size)
    {
        l = matrix[i].list;
        int a = 0;
        while (a < size)
        {
            printf("%d\t", l->valeur);
            l = l->next;
            a++;
        }
        printf("\n");
        i++;
    }
}

void Print_Matrix_File(array_Ty *Matrix, int nbr)
{
    l = malloc(sizeof(struct list_Ty));
    l = Matrix[0].list;
    int counter = 0;
    while (counter < nbr)
    {
        printf("\n%d -> %d \n", l->sommet, l->valeur);
        //l->next = malloc(sizeof(struct list_Ty));
        l = l->next;
        counter++;
    }
}

int RechercherValeurdeMatrix(array_Ty *matrix, int sommet, int position_file)
{
    l = malloc(sizeof(struct list_Ty));
    int val = 0;
    l = matrix[position_file].list;
    for (int i = 0; i < sommet; i++)
    {
        //l->next = malloc(sizeof(struct list_Ty));
        l = l->next;
        val = l->valeur;
    }
    return val;
}

int validationceroxfile(array_Ty *matrix2, int sommet, int nbr_vertices)
{
    l2 = malloc(sizeof(struct list_Ty));
    int valnew = 0;
    l2 = matrix2[sommet].list;
    for (int i = 0; i < nbr_vertices; i++)
    {
        if (l2->valeur == 1)
        {
            valnew = 1;
            break;
        }
        else
        {
            l2 = l2->next;
        }
    }
    return valnew;
}

int validationceroxcolonne(array_Ty *matrix2, int file, int nbr_vertices)
{
    l2 = malloc(sizeof(struct list_Ty));
    int valnew = 0;

    for (int i = 0; i < nbr_vertices; i++)
    {
        l2 = matrix2[i].list;

        for (int j = 0; j < file; j++)
        {
            //l2->next = malloc(sizeof(struct list_Ty));
            l2 = l2->next;
        }
        if (l2->valeur == 1)
        {
            valnew = 1;
        }
    }
    return valnew;
}

void FairCopiedeMatrix(array_Ty *matrix1, array_Ty *matrix2, int nbr_vertices)
{
    l1 = malloc(sizeof(struct list_Ty));
    l2 = malloc(sizeof(struct list_Ty));
    //printf("\n Matrice construi du graphe \n");
    for (int i = 0; i < nbr_vertices; i++)
    {
        l1 = matrix1[i].list;
        l2 = matrix2[i].list;
        for (int j = 0; j < nbr_vertices; j++)
        {
            if (i < j)
            {
                l2->valeur = l1->valeur;
                l1 = l1->next;
                l2 = l2->next;
            }
            else if (i > j)
            {
                l2->valeur = RechercherValeurdeMatrix(matrix1, i, j);
                l1 = l1->next;
                l2 = l2->next;
            }
            else
            {
                l1 = l1->next;
                l2 = l2->next;
            }
        }
    }
}

struct array_Ty *Prendre_sommetsnonconnexes(array_Ty *matrix2, int nbr_vertices)
{

    struct array_Ty *Matrix;

    Matrix = malloc(nbr_Vertices * sizeof(*Matrix));

    Matrix[0].sommet = 0;
    Matrix[0].list = NULL;
    list = malloc(sizeof(struct list_Ty));
    Matrix[0].list = list;
    list->sommet = 0;
    list->valeur = 0;
    list->next = NULL;

    int c = 0;

    for (int i = 0; i < nbr_Vertices; i++)
    {
        if (validationceroxfile(matrix2, i, nbr_Vertices) == 0 && validationceroxcolonne(matrix2, i, nbr_Vertices) == 0)
        {

            list->sommet = c;
            list->valeur = i;
            list->next = malloc(sizeof(struct list_Ty));
            list = list->next;
            c++;
        }
    }

    return Matrix;
}

unsigned int Nombre_effacer_sommets(array_Ty *Matrix_sommets_non_connexes, int nbr_vertices)
{
    l = malloc(sizeof(struct list_Ty));
    l = Matrix_sommets_non_connexes[0].list;
    int counter = 0;
    while (l->next != NULL && counter < nbr_Vertices)
    {
        l = l->next;
        counter++;
    }
    return counter;
}

unsigned int Nombre_aretes_relies_a_sommet_choisie(array_Ty *Matrix, int nbr_vertices, int sommet_choisie)
{
    l = malloc(sizeof(struct list_Ty));
    int i = 0;
    int counter = 0;
    l = Matrix[sommet_choisie].list;
    int a = 0;
    while (a < nbr_vertices)
    {
        if (l->valeur == 1)
        {
            counter++;
        }
        l = l->next;
        a++;
    }
    return counter;
}

struct array_Ty *GenerationMatriceconnexe(array_Ty *matrix2, array_Ty *matrix_non_connexe, int nbr_vertices_anciennes, int nbr_Vertices_nouvelle)
{
    array_Ty *Matrix_connexe = CreateMatrix_vide(nbr_Vertices_nouvelle);

    l = malloc(sizeof(struct list_Ty));
    l = matrix_non_connexe[0].list;
    l2 = malloc(sizeof(struct list_Ty));

    list = malloc(sizeof(struct list_Ty));
    l1 = malloc(sizeof(struct list_Ty));
    unsigned int cc = 0, co = 0;

    while (cc < nbr_vertices_anciennes)
    {

        list = matrix2[cc].list;

        if (l->valeur != cc)
        {

            l1 = Matrix_connexe[co].list;
            l2 = matrix_non_connexe[0].list;

            unsigned int co2 = 0;
            for (int j = 0; j < nbr_vertices_anciennes; j++)
            {

                //recorrer filas
                if (l2->valeur == j)
                {
                    if (l2->next == NULL)
                    {
                        list = list->next;
                    }
                    else
                    {
                        list = list->next;
                        l2 = l2->next;
                    }
                }
                else
                {
                    l1->sommet = co2;
                    l1->valeur = list->valeur;
                    l1->next = malloc(sizeof(struct list_Ty));
                    l1 = l1->next;
                    list = list->next;
                    co2++;
                }
            }
            co++;
        }
        else
        {
            if (cc > 0 && l->valeur == 0)
            {
                list->next = malloc(sizeof(struct list_Ty));
                list = list->next;
            }
            else
            {
                //printf("next \n");
                l = l->next;
                list->next = malloc(sizeof(struct list_Ty));
                list = list->next;
            }
        }
        cc++;
    }

    return Matrix_connexe;
}

int numero_aretes_graphe(array_Ty *matrixnouvelle, int nbr_nouvelles_vertices)
{
    l = malloc(sizeof(struct list_Ty));
    int i = 0;
    int counter = 0;
    while (matrixnouvelle[i].sommet < nbr_nouvelles_vertices)
    {
        l = matrixnouvelle[i].list;
        int a = 0;
        while (a < nbr_nouvelles_vertices)
        {
            if (l->valeur == 1)
            {
                counter++;
            }
            l = l->next;
            a++;
        }
        //printf("\n");
        i++;
    }
    counter = counter / 2;
    return counter;
}

int degree_moyen_aretes(array_Ty *matrixnouvelle, int nbr_nouvelles_vertices)
{
    l = malloc(sizeof(struct list_Ty));
    unsigned int i = 0;
    unsigned int degree = 0;
    int degreemoyen[nbr_nouvelles_vertices];

    while (matrixnouvelle[i].sommet < nbr_nouvelles_vertices)
    {
        l = matrixnouvelle[i].list;
        int a = 0;
        int counter = 0;
        while (a < nbr_nouvelles_vertices)
        {
            if (l->valeur == 1)
            {
                counter++;
            }
            l = l->next;
            a++;
        }
        degreemoyen[i] = counter;
        //printf("\n");
        i++;
    }

    for (int p = 0; p < nbr_nouvelles_vertices; p++)
    {
        degree = degree + degreemoyen[p];
    }

    degree = degree / nbr_nouvelles_vertices;

    return degree;
}

unsigned int getsommetRandom(int nbr_vertices)
{
    unsigned int a = 0, random = 0;
    while (random < MAX_TOURS)
    {
        a = rand() % nbr_vertices;
        random++;
    }
    return a;
}

struct array_Ty *Matrix_vertices_relies(array_Ty *matrix2, int sommet_choisie, int nbr_verticesrelies, int verticestotalmatrix)
{

    struct array_Ty *Matrix;
    printf("\nnbr_verticesrelies-> %d\n", nbr_verticesrelies);
    Matrix = malloc(nbr_verticesrelies * sizeof(*Matrix));

    Matrix[0].sommet = 0;
    Matrix[0].list = NULL;
    list = malloc(sizeof(struct list_Ty));
    Matrix[0].list = list;
    //list->sommet = 0;
    // list->valeur = 0;
    //list->next = NULL;
    printf("val sommet choisie: %d\n", sommet_choisie);
    l = malloc(sizeof(struct list_Ty));
    l = matrix2[sommet_choisie].list;

    for (int i = 0; i < verticestotalmatrix; i++)
    {
        if (l->valeur == 1)
        {
            //printf("[%d] -> [%d] ==1\t", l->sommet, l->valeur);
            list->sommet = l->sommet;
            list->valeur = l->valeur;
            list->next = malloc(sizeof(struct list_Ty));
            list = list->next;

            l = l->next;
            //printf("finmmmmmm == 1\n");
        }
        else
        {
            //printf("[%d] -> [%d] ==0,\t", l->sommet, l->valeur);
            l = l->next;
        }
    }

    return Matrix;
}

int get_nombre_des_aretes_du_Sousgraphe(array_Ty *matrixc, array_Ty *matrix, array_Ty *matrix2, int nbr_aretes_relies)
{
    unsigned int counter = 0, c1 = 0, c2 = 0;
    l1 = malloc(sizeof(struct list_Ty));
    l1 = matrix[0].list;

    l2 = malloc(sizeof(struct list_Ty));
    l2 = matrix2[0].list;
    l2 = l2->next;

    list = malloc(sizeof(struct list_Ty));

    while (c1 < nbr_aretes_relies)
    {
        while (c2 < nbr_aretes_relies)
        {
            l2 = matrix2[0].list;
            while (l2->sommet <= l1->sommet)
            {
                l2 = l2->next;
            }

            if (RechercherValeurdeMatrix(matrixc, l1->sommet, l2->sommet))
            {
                counter++;
            }

            l2 = l2->next;
            c2++;
        }
        l1 = l1->next;
        c1++;
    }

    return counter;
}

int calculerCliqueMaximal(int nbr_voisins_de_sommet_choisie)
{
    return (nbr_voisins_de_sommet_choisie * (nbr_voisins_de_sommet_choisie - 1)) / 2;
}
/*
void main()
{
    nbr_Vertices = rand();
    printf("nb_sommets_audebut:%d\n", nbr_Vertices);
    array_Ty *Matrix1 = CreateMatrix();
    array_Ty *Matrix2 = CreateMatrix_vide(nbr_Vertices);
    array_Ty *MatrixFinalConnexe;
    array_Ty *Matrix_forcee = CreateMatrix_forcee(nbr_Vertices);
    FairCopiedeMatrix(Matrix1, Matrix2, nbr_Vertices);

    array_Ty *Matrixsommetsnonconnexes = Prendre_sommetsnonconnexes(Matrix2, nbr_Vertices);
    nbr_sommets_non_connexes = Nombre_effacer_sommets(Matrixsommetsnonconnexes, nbr_Vertices);
    nbr_Vertices_nouvelle = nbr_Vertices - nbr_sommets_non_connexes;
    if (nbr_Vertices_nouvelle > 0 && nbr_Vertices_nouvelle < nbr_Vertices)
    {
        printf("Matrice Connexe\n");
        MatrixFinalConnexe = GenerationMatriceconnexe(Matrix2, Matrixsommetsnonconnexes, nbr_Vertices, nbr_Vertices_nouvelle);
        PrintMatrix(MatrixFinalConnexe, nbr_Vertices_nouvelle);
    }
    else
    {
        MatrixFinalConnexe = Matrix2;
        printf("Matrice Connexe\n");
        PrintMatrix(MatrixFinalConnexe, nbr_Vertices);
    }
    printf("aretes du graphe: %d\n", numero_aretes_graphe(MatrixFinalConnexe, nbr_Vertices_nouvelle));
    printf("degree moyen du graphe: %d\n", degree_moyen_aretes(MatrixFinalConnexe, nbr_Vertices_nouvelle));
    unsigned int sommetRandom = getsommetRandom(nbr_Vertices_nouvelle);
    unsigned int nbr_aretes_relies = Nombre_aretes_relies_a_sommet_choisie(MatrixFinalConnexe, nbr_Vertices_nouvelle, sommetRandom);
    printf("getsommetrandom: %d\n", sommetRandom);
    printf("numero_aretes_graphe: %d\n", nbr_aretes_relies);
    printf("*--------------generation sous-graphe------------*");
    array_Ty *Matrixsommets_relies = Matrix_vertices_relies(MatrixFinalConnexe, sommetRandom, nbr_aretes_relies, nbr_Vertices_nouvelle);
    Print_Matrix_File(Matrixsommets_relies, nbr_aretes_relies);
    unsigned int extra_aretes = get_nombre_des_aretes_du_Sousgraphe(MatrixFinalConnexe, Matrixsommets_relies, Matrixsommets_relies, nbr_aretes_relies);
    printf("nbr_aretes_sousgraphe_extras: %d\n", extra_aretes);
    int nbr_total_aretes_sous_graphe = extra_aretes + nbr_aretes_relies;
    printf("nbr_aretes_sousgraphe_total: %d\n", nbr_total_aretes_sous_graphe);
    printf("*--------------clique maximal------------*");
    printf("\nclique maximal du sousgraphe= %d", calculerCliqueMaximal(nbr_aretes_relies));
}
*/
/*
void main()
{
    nbr_Vertices = 4;
=======

/* struct list_Ty *Recherche_sommetsnonconnexes(array_Ty *matrix2, int nbr_vertices)
{   
    struct list_Ty *sommets_nonconnexes;
    sommets_nonconnexes = malloc(nbr_Vertices * sizeof(*sommets_nonconnexes));

    for (int i = 0; i < nbr_Vertices; i++)
    {
        if (validationceroxfile(matrix2, i, nbr_Vertices) == 0 && validationceroxcolonne(matrix2, i, nbr_Vertices) == 0)
        {
            sommets_nonconnexes->sommet = i;
            printf("sommetnulle: %d", sommets_nonconnexes->sommet);
        }
        sommets_nonconnexes = sommets_nonconnexes->next;
    }
    return sommets_nonconnexes;
}
*/