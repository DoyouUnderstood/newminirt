#include "../include/mathematique.h"

// fonction pour determiner le determinant d'un matrice 4x4
double determinant4x4(t_matrix mat) 
{
    double det = 0.0;
    for (int col = 0; col < 4; col++) {
        double subMatrice4x4[3][3];
        getSubMatrice4x4(mat, subMatrice4x4, 0, col);
        double minor = determinant3x3(subMatrice4x4);
        double cofactor = (col % 2 == 0 ? 1 : -1) * minor;
        det += mat.m[0][col] * cofactor;
    }
    return det;
}
// calcul le determinant d'une Matrice 3x3
double determinant3x3(double matrix[3][3]) 
{
    double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                 matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                 matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    return det;
}

// fonction pour calculer le determinant d'un matrice 2x2
double determinant2x2(double Matrice4x4[2][2]) 
{
    return (Matrice4x4[0][0] * Matrice4x4[1][1] - Matrice4x4[0][1] * Matrice4x4[1][0]);
}

// fonction pour calculer le determinant d'un sous matrice (mineur)
double calculate_minor(t_matrix mat, int row, int col)
{
    double minor[3][3];
    double det;
    for (int i = 0, mi = 0; i < 4; ++i) {
        if (i == row) continue;
        for (int j = 0, mj = 0; j < 4; ++j) {
            if (j == col) continue;
            minor[mi][mj] = mat.m[i][j];
            mj++;
        }
        mi++;
    }
    det = determinant3x3(minor);
    return det;
}

// fonction pour calculer le cofactor d'un matrice
t_matrix calculate_cofactor_matrice(t_matrix mat) 
{
    t_matrix cofactor;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double sign = (i + j) % 2 == 0 ? 1.0 : -1.0;
            cofactor.m[i][j] = sign * calculate_minor(mat, i, j);
        }
    }
    return cofactor;
}

// fonction pour extraire une sous-matrice 3x3 d'une matrice 4x4 en excluant une ligne et une colonne spécifiques.
void getSubMatrice4x4(t_matrix mat, double subMatrice4x4[3][3], int excluding_row, int excluding_col) 
{
    int di = 0;
    for (int i = 0; i < 4; ++i) {
        if (i == excluding_row) 
            continue;
        int dj = 0;
        for (int j = 0; j < 4; ++j) {
            if (j == excluding_col) 
                continue;
            subMatrice4x4[di][dj] = mat.m[i][j];
            dj++;
        }
        di++;
    }
}
