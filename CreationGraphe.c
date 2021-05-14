#include <stdio.h>
#include <stdlib.h>

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

            if ( i == j || i == 2 || j == 2 || i == 1 || j == 1 )
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

        }else{
        l2 = l2->next;}
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
    Matrix[0].list=list;
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
    printf("val_matrix: %d\n", l->valeur);
    while (l->next != NULL && counter < nbr_Vertices)
    {

        l = l->next;
        counter++;
    }
    printf("counter: %d\n", counter);
    return counter;
}

struct array_Ty *GenerationMatriceconnexe(array_Ty *matrix2, array_Ty *matrix_non_connexe, int nbr_vertices_anciennes, int nbr_Vertices_nouvelle)
{
    printf("nombre_vertices_nouvelle-> %d\n", nbr_Vertices_nouvelle);
    array_Ty *Matrix_connexe = CreateMatrix_vide(nbr_Vertices_nouvelle); //crear matriz nueva

    //inicializacion de matrix_non_connexe
    l = malloc(sizeof(struct list_Ty)); //creando lista
    l = matrix_non_connexe[0].list;     // asignando lista a matrix_non_connexe

    //inicializacion de matrix normal
    list = malloc(sizeof(struct list_Ty)); //creando lista

    //inicializacion de MatrixConnexe
    l1 = malloc(sizeof(struct list_Ty));
    //cc= todo
    //co= solo connexes
    unsigned int cc = 0, co = 0;
    while (cc < nbr_vertices_anciennes && l->next != NULL)
    {
        printf("cima de matrix-> %d", l->valeur);

        if (l->valeur != cc) //aqui trabajar , l->valeur es cima de matrix_non_connexe , cc es la cima de la nueva matriz
        {
            printf("sommet connexe %d\n", cc); //entrar a colonne 1
            l1 = Matrix_connexe[co].list;      // asignar lista de matrix connexe
            list = matrix2[cc].list;           //inicializar matrix2 en una lista
            for (int j = 0; j < nbr_vertices_anciennes; j++)
            { //recorrer filas
                if (l->valeur == j)
                {
                    list = list->next;
                    l = l->next;
                    printf("val non connexe: %d\n", j);
                }
                else
                {
                    printf("val connexe: %d\n", j);
                    l1->sommet = co;
                    l1->valeur = l->valeur;
                    list = list->next;
                    co++;
                }
            }
            cc++;
        }
        else
        {

            printf("sommet non connexe %d\n", cc);
            cc++;
            //list=list->next;
        }
    }

    return Matrix_connexe;
}
void main()
{
    nbr_Vertices = 5;
    printf("nb_sommets_audebut:%d\n", nbr_Vertices);
    array_Ty *Matrix1 = CreateMatrix();
    array_Ty *Matrix2 = CreateMatrix_vide(nbr_Vertices);
    array_Ty *MatrixFinalConnexe;
    array_Ty *Matrix_forcee = CreateMatrix_forcee(nbr_Vertices);
    FairCopiedeMatrix(Matrix_forcee, Matrix2, nbr_Vertices); // Atento: Cambiar por la Matrix1 apres
    PrintMatrix(Matrix2, nbr_Vertices);
    printf("---logique--\n");
    array_Ty *Matrixsommetsnonconnexes = Prendre_sommetsnonconnexes(Matrix2, nbr_Vertices);    //lista de sommets no connexes matrice[0]
    nbr_sommets_non_connexes = Nombre_effacer_sommets(Matrixsommetsnonconnexes, nbr_Vertices); // conteo de la matrice[0] con sus sommets
    nbr_Vertices_nouvelle = nbr_Vertices - nbr_sommets_non_connexes;                           // creation de variable pour obtenir une nouveau nombre des vertices
    printf("val nbr_sommets_non_connexes: %d", nbr_sommets_non_connexes);
    if (nbr_Vertices_nouvelle > 0 && nbr_Vertices_nouvelle < nbr_Vertices)
    {
        MatrixFinalConnexe = GenerationMatriceconnexe(Matrix2, Matrixsommetsnonconnexes, nbr_Vertices, nbr_Vertices_nouvelle);
    }
    else
    {
        printf("Matrix ancienne reste");
    }
}