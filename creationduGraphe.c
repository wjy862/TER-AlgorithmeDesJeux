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
struct list_Ty *list;
struct list_Ty *l;

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
    int i = 0;
    while (matrix[i].sommet < size)
    {
        l = matrix[i].list;
        printf("\nsommet :%d\n", i);
        int a = 0;
        while (a < size)
        {
            printf("%d->%d\t", l->sommet, l->valeur);
            l = l->next;
            a++;
        }
        printf("\n\n");
        i++;
    }
}

int RechercherValeurdeMatrix(array_Ty *matrix, int sommet, int position_file)
{   int val=0;
    l = matrix[position_file].list;
    for(int i=0;i<=sommet;i++)printf("heyyy!");l=l->next;
    
    val=l->valeur;
    return val;
}

void Completer_Matrice(array_Ty *matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        l=matrix[i].list;
        for (int j = l->sommet; j < size; j++)
        {
            //printf("\ni:|%d->j:%d \n", i, l->sommet);
            printf("\ni:|%d->j:%d == %d\n", i, l->sommet, RechercherValeurdeMatrix(matrix, j, i));
            l=l->next;
        }
    }
  
}

void main()
{
    nbr_Vertices = 5;
    printf("nb_sommets:%d", nbr_Vertices);
    array_Ty *Matrix = CreateMatrix();
    PrintMatrix(Matrix, nbr_Vertices);

    printf("--------completer Matrice----");
    Completer_Matrice(Matrix, nbr_Vertices);
}