#include "../include/mathematique.h"

// Calcule le vecteur réfléchi à partir d'un vecteur incident et d'un vecteur normal
t_tuple reflect(t_tuple incident, t_tuple normal)
{
    double dot;
    t_tuple scaled_normal;
    t_tuple reflection;
    dot = dot_product(incident, normal);
    scaled_normal = vect_scale(normal, 2 * dot);
    reflection = subtract_vectors(incident, scaled_normal);

    return (reflection);
}
