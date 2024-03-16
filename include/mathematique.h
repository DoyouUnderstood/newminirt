#ifndef MATHEMATIQUE_H
#define MATHEMATIQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// !!!! un tuple avec w = 0 est un vecteur !!!!
typedef struct s_tuple
{
    double x;
    double y;
    double z;
    double w;
} t_tuple;

typedef struct s_matrix
{
    float m[4][4];
} t_matrix;

// ============ MATRIX OPERATION ================

t_matrix	init_matrice_identite();
t_matrix 	multiply_matrices(t_matrix Ma, t_matrix Mb);
t_matrix 	transpose_matrix(t_matrix mat);
t_matrix 	inverse_matrix(t_matrix mat);
void		draw_matrice(t_matrix matrice);
int 		is_same_matrice(t_matrix Ma, t_matrix Mb);
t_tuple 	multiply_matrix_by_tuple(t_matrix mat, t_tuple tup);

// ========= DETERMINANT COFACTEUR =============

double		determinant4x4(t_matrix mat);
void 		getSubMatrice4x4(t_matrix mat, double subMatrice4x4[3][3], int excluding_row, int excluding_col);
double 		determinant3x3(double matrix[3][3]);
double 		determinant2x2(double Matrice4x4[2][2]);
double 		calculate_minor(t_matrix mat, int row, int col);
t_matrix 	calculate_cofactor_matrice(t_matrix mat);

// ========== MATRIX TRANSFORM ===============

t_tuple		reflectPoint(t_tuple point, char axis);
t_tuple		scale(t_tuple point, double sx, double sy, double sz);
t_matrix	rotation_y(double angle);
t_matrix	rotation_x(double angle);
t_matrix	shearing_matrix(double xy, double xz, double yx, double yz, double zx, double zy);
t_matrix	rotation_z(double angle);
t_matrix	scaling_matrix(double sx, double sy, double sz);
t_matrix	translation_matrix(double dx, double dy, double dz);

// ============== POINT ===============

t_tuple		point(double x, double y, double z);
t_tuple		point_add_vector(t_tuple point, t_tuple vect);
t_tuple		multiply_point(t_tuple a, double scalar);
t_tuple		subtract_vector_from_point(t_tuple point, t_tuple vect);

// ============== VECTEUR ===============

t_tuple		vector(double x, double y, double z);
t_tuple		add_two_vectors(t_tuple v1, t_tuple v2);
t_tuple		subtract_vectors(t_tuple a, t_tuple b); 
t_tuple		vect_scale(t_tuple v, double scalar);
double		dot_product(t_tuple a, t_tuple b);
t_tuple		multiply_vec(t_tuple a, double scalar);
t_tuple		normalize_vector(t_tuple a);

#endif