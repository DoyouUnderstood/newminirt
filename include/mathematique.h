#ifndef MATHEMATIQUE_H
#define MATHEMATIQUE_H

// un tuple avec w = 0 est un vecteur 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Definition d' une précision standard pour la comparaison des tuples.
#define TUPLE_EPSILON 1e-6

typedef struct s_sphere t_sphere;

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

void        draw_matrice(t_matrix matrice);
t_tuple		reflectPoint(t_tuple point, char axis);
t_tuple		scale(t_tuple point, double sx, double sy, double sz);
t_matrix	rotation_y(double angle);
t_matrix	rotation_x(double angle);
t_matrix	shearing_matrix(double xy, double xz, double yx, double yz, double zx, double zy);
t_matrix	rotation_z(double angle);
t_matrix	scaling_matrix(double sx, double sy, double sz);
t_matrix	translation_matrix(double dx, double dy, double dz);
bool        matrix_is_identity(t_matrix mat);

// ============== POINT ===============

t_tuple     point_sub(t_tuple point, t_tuple point2);
t_tuple		point(double x, double y, double z);
t_tuple		point_add_vector(t_tuple point, t_tuple vect);
t_tuple		multiply_point(t_tuple a, double scalar);
t_tuple		subtract_vector_from_point(t_tuple point, t_tuple vect);

// ============== VECTEUR ===============

t_tuple		vector_create(double x, double y, double z);
t_tuple		add_two_vectors(t_tuple v1, t_tuple v2);
t_tuple		subtract_vectors(t_tuple a, t_tuple b); 
t_tuple		vect_scale(t_tuple v, double scalar);
double		dot_product(t_tuple a, t_tuple b);
t_tuple		multiply_vec(t_tuple a, double scalar);
t_tuple		normalize_vector(t_tuple a);
bool        eq_tuple(t_tuple a, t_tuple b);
t_tuple     vector_negate(t_tuple v);

// ============== NORMAL ===============

t_tuple     normal_at(const t_sphere* sphere, t_tuple world_point);

t_tuple reflect(t_tuple incident, t_tuple normal);

#endif