#include <stdio.h>
#include <stdlib.h>

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
struct list_Ty *l1;
struct list_Ty *l2;

struct array_Ty *CreateMatrix_vide()
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

int RechercherValeurdeMatrix(array_Ty *matrix, int sommet, int position_file)
{
    int val = 0;
    l = matrix[position_file].list;
    for (int i = 0; i < sommet; i++)
    {
        l = l->next;
        val = l->valeur;
    }

    return val;
}

void Print_Moitie_Matrix(array_Ty *matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        l = matrix[i].list;
        for (int j = i; j < size - 1; j++)
        {
            printf("\nmmmmm\n");
            printf("\ni:|%d->j:%d == %d\n", i, l->sommet, RechercherValeurdeMatrix(matrix, j, i));
            l = l->next;
        }
    }
}

int validationceroxfile(array_Ty *matrix2, int sommet, int nbr_vertices)
{
    int valnew = 0;
    l2 = matrix2[sommet].list;
    for (int i = 0; i < nbr_vertices; i++)
    {
        if (l2->valeur == 1)
        {
            valnew = 1;
        }
        l2 = l2->next;
    }
    return valnew;
}

int validationceroxcolonne(array_Ty *matrix2, int file, int nbr_vertices)
{
    int valnew = 0;
    
    for (int i = 0; i < nbr_vertices; i++)
    {
        l2 = matrix2[i].list;

        for (int j = 0; i < file; i++)
        {    
          l2=l2->next; 
        }
        if(l2->valeur == 1)
        {   
            valnew = 1;
        }
    }
    return valnew;
}

void FairCopiedeMatrix(array_Ty *matrix1, array_Ty *matrix2, int nbr_vertices)
{
    printf("\n Matrice du graphe \n");
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

void main()
{
    nbr_Vertices = 6;
    printf("nb_sommets:%d\n", nbr_Vertices);
    array_Ty *Matrix1 = CreateMatrix();
    array_Ty *Matrix2 = CreateMatrix_vide();
    FairCopiedeMatrix(Matrix1, Matrix2, nbr_Vertices);
    PrintMatrix(Matrix2, nbr_Vertices);
    printf("\nC'es connexe la sommet :%d   -->%d", 0, validationceroxfile(Matrix2, 0, nbr_Vertices));
    printf("\nC'es connexe la sommet :%d   -->%d", 1, validationceroxfile(Matrix2, 1, nbr_Vertices));
    printf("\nC'es connexe la sommet :%d   -->%d", 2, validationceroxfile(Matrix2, 2, nbr_Vertices));
    printf("\nC'es connexe la sommet :%d   -->%d", 3, validationceroxfile(Matrix2, 3, nbr_Vertices));

    printf("\n\n\nFile :%d   -->%d", 0, validationceroxcolonne(Matrix2,0,nbr_Vertices));
    printf("\n\n\nFile :%d   -->%d", 1, validationceroxcolonne(Matrix2,1,nbr_Vertices));
    printf("\n\n\nFile :%d   -->%d", 2, validationceroxcolonne(Matrix2,2,nbr_Vertices));
    printf("\n\n\nFile :%d   -->%d", 3, validationceroxcolonne(Matrix2,3,nbr_Vertices));
    

}