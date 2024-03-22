#include "../include/mathematique.h"

// Fonction pour initialiser une matrice 4x4 d'identite avec des 1 lors que i et j sont pareil. 0 sinon 
t_matrix matrix_init_identity() {
    t_matrix matrice;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrice.m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
    return (matrice);
}

// Fonction d'affichage de matrice
void matrix_draw(t_matrix matrice) 
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%0.2f ", matrice.m[i][j]);
        }
        printf("\n");
    }
}

// fonction booleen pour determiner si une matrix est une matrice d'identite.
bool matrix_is_identity(t_matrix mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((i == j && mat.m[i][j] != 1.0) || (i != j && mat.m[i][j] != 0.0)) {
                return false;
            }
        }
    }
    return true;
}

// Fonction pour multiplier deux matrices 4x4
t_matrix matrix_multiply(t_matrix Ma, t_matrix Mb) 
{
    t_matrix resultat;
    int i;
    int j;
    int k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            resultat.m[i][j] = 0;
            for (k = 0; k < 4; k++) {
                resultat.m[i][j] += Ma.m[i][k] * Mb.m[k][j];
            }
        }
    }
    return resultat;
}

// Fonction qui determine si ce sont les memes matrices
int is_same_matrice(t_matrix Ma, t_matrix Mb)
{
    int i = 0;
    int j = 0;

    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            if (Ma.m[i][j] != Mb.m[i][j])
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

// Fonction pour transposez une matrice, cad transformez ses lignes en colonnes et ses colonnes en lignes. (Utile pour l'ombrage)
t_matrix matrix_transpose(t_matrix mat) 
{
    t_matrix transposed;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            transposed.m[j][i] = mat.m[i][j];
        }
    }
    return transposed;
}

//fonction pour inverser les matrix.
t_matrix matrix_inverse(t_matrix mat) {
    double det = determinant4x4(mat);
    if (det == 0) {
        fprintf(stderr, "Matrix is not invertible.\n");
        exit(EXIT_FAILURE);
    }
    t_matrix cofactor = calculate_cofactor_matrix(mat);
    t_matrix adjugate = matrix_transpose(cofactor);
    t_matrix inverse;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            inverse.m[i][j] = adjugate.m[i][j] / det;
        }
    }

    return (inverse);
}

//fonction pour multiplier la matrices par un point ou vecteur.
t_tuple matrix_multiply_by_tuple(t_matrix mat, t_tuple tup) 
{
    t_tuple result;

    result.x = mat.m[0][0] * tup.x + mat.m[0][1] * tup.y + mat.m[0][2] * tup.z + mat.m[0][3] * tup.w;
    result.y = mat.m[1][0] * tup.x + mat.m[1][1] * tup.y + mat.m[1][2] * tup.z + mat.m[1][3] * tup.w;
    result.z = mat.m[2][0] * tup.x + mat.m[2][1] * tup.y + mat.m[2][2] * tup.z + mat.m[2][3] * tup.w;
    result.w = mat.m[3][0] * tup.x + mat.m[3][1] * tup.y + mat.m[3][2] * tup.z + mat.m[3][3] * tup.w;

    return (result);
}