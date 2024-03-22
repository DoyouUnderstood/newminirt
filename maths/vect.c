#include "../include/mathematique.h"

// Fonction pour créer un vecteur
t_tuple vector_create(double x, double y, double z) 
{
    return (t_tuple){x, y, z, 0.0};
}

//fonction pour ajouter 2 vecteurs
t_tuple add_two_vectors(t_tuple v1, t_tuple v2)
 {
    t_tuple result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    result.w = 0.0;
    return result;
}

// fonction pour soustraire les vecteurs.
t_tuple subtract_vectors(t_tuple a, t_tuple b) 
{
    t_tuple result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w;
    return result;
}

//fonction de mise a l'echelle d'un vecteur.
t_tuple vect_scale(t_tuple v, double scalar)
{
    t_tuple result;

    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    result.w = v.w;

    return result;
}

// fonction de produit scalaire de vecteur. 
double dot_product(t_tuple a, t_tuple b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

//fonction pour multiplier toute les composantes d'un vec pour un scalaire
t_tuple multiply_vec(t_tuple a, double scalar)
{
    t_tuple result;

    result.x = a.x * scalar;
    result.y = a.y * scalar;
    result.z = a.z * scalar;
    result.w = a.w;

    return result;
}

//fonction pour normaliser un vecteur 
t_tuple normalize_vector(t_tuple a) 
{
    t_tuple result;
    double length;
    
    length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    if (length != 0) 
    {
        result.x = a.x / length;
        result.y = a.y / length;
        result.z = a.z / length;
        result.w = 0;
    } else 
    {
        // Si le vecteur est de longueur nulle, retourne un vecteur nul.
        result.x = result.y = result.z = result.w = 0;
    }
    return (result);
}

// Fonction pour comparer deux tuples avec la précision standard
bool eq_tuple(t_tuple a, t_tuple b) 
{
    return fabs(a.x - b.x) < TUPLE_EPSILON &&
           fabs(a.y - b.y) < TUPLE_EPSILON &&
           fabs(a.z - b.z) < TUPLE_EPSILON &&
           fabs(a.w - b.w) < TUPLE_EPSILON;
}

// Fonction pour inverser un vecteur.
t_tuple vector_negate(t_tuple v) 
{
    t_tuple result;

    result.x = -v.x;
    result.y = -v.y;
    result.z = -v.z;
    result.w = v.w;

    return result;
}