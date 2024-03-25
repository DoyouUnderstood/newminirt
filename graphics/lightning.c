#include "../include/graphics.h"

// fonction qui calcule la couleurs d'un pixel.
#include <stdio.h>
#include <math.h>

// Ajoutez ici la définition de vos structures t_material, t_light, t_tuple, t_color
// et les prototypes de vos fonctions vector_normalize, tuple_subtract, vector_dot, reflect, color_multiply, color_multiply_scalar, color_add

// t_color lighting(const t_material *material, const t_light *light, const t_tuple *position, const t_tuple *eyev, const t_tuple *normalv) {
//     printf("Lighting function inputs:\n");
//     printf("- Position: (%f, %f, %f)\n", position->x, position->y, position->z);
//     printf("- Eye Vector: (%f, %f, %f)\n", eyev->x, eyev->y, eyev->z);
//     printf("- Normal Vector: (%f, %f, %f)\n", normalv->x, normalv->y, normalv->z);
//     printf("- Light Position: (%f, %f, %f), Intensity: (%f, %f, %f)\n", light->pos.x, light->pos.y, light->pos.z, light->intensity.r, light->intensity.g, light->intensity.b);
//     printf("- Material: Ambient: %f, Diffuse: %f, Specular: %f, Shininess: %f\n", material->ambient, material->diffuse, material->specular, material->shininess);

//     t_color effective_color = color_multiply(material->color, light->intensity);
//     printf("Effective Color: (%f, %f, %f)\n", effective_color.r, effective_color.g, effective_color.b);

//     t_tuple lightv = vector_normalize(tuple_subtract(light->pos, *position));
//     printf("Light Vector: (%f, %f, %f)\n", lightv.x, lightv.y, lightv.z);

//     t_color ambient = color_multiply_scalar(effective_color, material->ambient);
//     printf("Ambient Color: (%f, %f, %f)\n", ambient.r, ambient.g, ambient.b);

//     double light_dot_normal = vector_dot(lightv, *normalv);
//     t_color diffuse;
//     t_color specular;

//     if (light_dot_normal < 0) {
//         diffuse = (t_color){0, 0, 0};
//         specular = (t_color){0, 0, 0};
//         printf("Light is on the other side of the surface, no diffuse or specular contribution.\n");
//     } else {
//         diffuse = color_multiply_scalar(effective_color, material->diffuse * light_dot_normal);
//         printf("Diffuse Color: (%f, %f, %f)\n", diffuse.r, diffuse.g, diffuse.b);

//         t_tuple reflectv = reflect(vector_negate(lightv), *normalv);
//         double reflect_dot_eye = vector_dot(reflectv, *eyev);

//         if (reflect_dot_eye <= 0) {
//             specular = (t_color){0, 0, 0};
//             printf("Eye does not catch the reflection, no specular contribution.\n");
//         } else {
//             double factor = pow(reflect_dot_eye, material->shininess);
//             specular = color_multiply_scalar(light->intensity, material->specular * factor);
//             printf("Specular Color: (%f, %f, %f)\n", specular.r, specular.g, specular.b);
//         }
//     }

//     t_color final_color = color_add(color_add(ambient, diffuse), specular);
//     printf("Final Color: (%f, %f, %f)\n", final_color.r, final_color.g, final_color.b);

//     return final_color;
// }

 t_color lighting(const t_material *material, const t_light *light, const t_tuple *position, const t_tuple *eyev, const t_tuple *normalv) 
{
    t_color effective_color = color_multiply(material->color, light->intensity);

    // Trouver la direction de la lumière
    t_tuple lightv = vector_normalize(tuple_subtract(light->pos, *position));

    // Calculer l'ambiant
    t_color ambient = color_multiply_scalar(effective_color, material->ambient);

    double light_dot_normal = vector_dot(lightv, *normalv);
    t_color diffuse;
    t_color specular;

    if (light_dot_normal < 0) {
        diffuse = (t_color){0, 0, 0};
        specular = (t_color){0, 0, 0};
    } else {
        diffuse = color_multiply_scalar(effective_color, material->diffuse * light_dot_normal);
        t_tuple reflectv = reflect(vector_negate(lightv), *normalv);
        double reflect_dot_eye = vector_dot(reflectv, *eyev);

        if (reflect_dot_eye > 0) {
            double factor = pow(reflect_dot_eye, material->shininess);
            specular = color_multiply_scalar(light->intensity, material->specular * factor);
        } else
            specular = (t_color){0, 0, 0};
    }
    return color_add(color_add(ambient, diffuse), specular);
}