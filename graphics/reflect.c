#include "../include/mathematique.h"
#include "../include/shape.h"

// Calcule le vecteur réfléchi à partir d'un vecteur incident et d'un vecteur normal
t_tuple reflect(t_tuple incident, t_tuple normal)
{
    double dot;
    t_tuple scaled_normal;
    t_tuple reflection;
    dot = dot_product(incident, normal);
    scaled_normal = vect_scale(normal, 2 * dot);
    reflection = subtract_vectors   (incident, scaled_normal);

    return (reflection);
}

t_material default_material() 
{
    t_material m;

    m.color = (t_color){255, 255, 255};
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.shininess = 200.0;

    return m;
}
