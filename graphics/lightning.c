#include "../include/graphics.h"

// fonction qui calcule la couleurs d'un pixel.
t_color lighting(t_material material, t_light light, t_tuple position, t_tuple eyev, t_tuple normalv) 
{
    t_color effective_color = color_multiply(material.color, light.intensity);

    // Trouver la direction de la lumière
    t_tuple lightv = vector_normalize(tuple_subtract(light.pos, position));

    // Calculer l'ambiant
    t_color ambient = color_multiply_scalar(effective_color, material.ambient);

    // light_dot_normal représente le cosinus de l'angle entre le vecteur lumière et le vecteur normal.
    double light_dot_normal = vector_dot(lightv, normalv);
    t_color diffuse;
    t_color specular;

    if (light_dot_normal < 0) {
        // La lumière est derrière l'objet
        diffuse = (t_color){.r = 0, .g = 0, .b = 0};
        specular = (t_color){.r = 0, .g = 0, .b = 0};
    } else {
        // Calculer le diffus
        diffuse = color_multiply_scalar(effective_color, material.diffuse * light_dot_normal);

        // Refléter le vecteur lumière autour du vecteur normal
        t_tuple reflectv = reflect(vector_negate(lightv), normalv);
        double reflect_dot_eye = vector_dot(reflectv, eyev);

        if (reflect_dot_eye <= 0) {
            specular = (t_color){.r = 0, .g = 0, .b = 0};
        } else {
            double factor = pow(reflect_dot_eye, material.shininess);
            specular = color_multiply_scalar(light.intensity, material.specular * factor);
        }
    }
    // Additionner ambiant, diffus et spéculaire
    return color_add(color_add(ambient, diffuse), specular);
}