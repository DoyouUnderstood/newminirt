#include "../include/mathematique.h"

t_tuple tuple_subtract(t_tuple a, t_tuple b) 
{
    t_tuple result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w;
    return (result);
}

// Fonction pour comparer deux tuples avec la précision standard
bool tuple_eq(t_tuple a, t_tuple b) 
{
    return fabs(a.x - b.x) < TUPLE_EPSILON &&
           fabs(a.y - b.y) < TUPLE_EPSILON &&
           fabs(a.z - b.z) < TUPLE_EPSILON &&
           fabs(a.w - b.w) < TUPLE_EPSILON;
}

// Fonction Applique une mise à l'échelle sur un point ou un vecteur.
t_tuple tuple_scale(t_tuple point, double sx, double sy, double sz)
{
    point.x *= sx;
    point.y *= sy;
    point.z *= sz;
    return point;
}