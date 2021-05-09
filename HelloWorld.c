#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct array_Ty array_Ty;
struct array_Ty
{
    int sommet;
    struct list_Ty *list;
};

typedef struct list_Ty list_Ty;
struct list_Ty
{
    int valeur;
    int sommet;
    struct list_Ty *next;
};

int nbr_Vertices;
int additionalVertices = 0;
int *ptr;
struct list_Ty *list;
struct list_Ty *l;

struct array_Ty *CreateMatrix(int *f)
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
             int n = rand() % 2;
            if (!Matrix[i].list)
                Matrix[i].list = list;
            else
            {
                list->next = malloc(sizeof(struct list_Ty));
                list = list->next;
            }
            list->sommet = j;
            list->valeur = n;
            list->next = NULL;
        }
    }
    return Matrix;
}

void PrintVectorSpecifique(array_Ty *matrix, int indice)
{
    l = matrix[indice].list;
    printf("|i|-> %d -> \t", matrix[indice].sommet);
    while (l != NULL)
    {
        printf(" %d , %0.2f", l->sommet, l->valeur);
        l = l->next;
    }
    printf("\n");
}

void PrintMatrix(array_Ty *matrix, int size)
{

    int i = 0;
    while (matrix[i].sommet < size-1)
    {
        l = matrix[i].list;
        printf("\n-sommet_:%d-\n", i);
        int a=0;
        while (a < size-1)
        {
            printf("|vo-:%d->val-:%d|\t", l->sommet, l->valeur);
            l = l->next;
            a++;
        }
        printf("\n\n");
        i++;
    }
}

void PrintVector(float *vct, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%f - ", vct[i]);
    }
    printf("\n");
}


int main()
{
    nbr_Vertices = rand();
    printf("nb_sommets:%d",nbr_Vertices);
    int *f = malloc(nbr_Vertices * sizeof(int));
    array_Ty *Matrix = CreateMatrix(f);

    PrintMatrix(Matrix,nbr_Vertices);
    return 0;
}