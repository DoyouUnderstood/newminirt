#include "../include/ray.h"

// Fonction pour initialiser un rayon
t_ray create_ray(t_tuple origin, t_tuple direction) {
    t_ray ray;
    ray.origin = origin;
    ray.direction = direction;
    return ray;
}

// Fonction pour afficher un rayon
void print_ray(t_ray ray) {
    printf("Ray Origin: (%.2f, %.2f, %.2f)\n", ray.origin.x, ray.origin.y, ray.origin.z);
    printf("Ray Direction: (%.2f, %.2f, %.2f)\n", ray.direction.x, ray.direction.y, ray.direction.z);
}

// Fonction pour calculer le point à la distance t le long du rayon
t_tuple position(t_ray ray, double t) 
{
    t_tuple displacement = multiply_point(ray.direction, t);
    return (point_add_vector(ray.origin, displacement));
}

t_ray transform_ray(t_matrix mat, t_ray ray) {
    t_ray transformed_ray;
    transformed_ray.origin = multiply_matrix_by_tuple(mat, ray.origin);
    transformed_ray.direction = multiply_matrix_by_tuple(mat, ray.direction);

    return transformed_ray;
}


// void throw_ray(t_sphere *sphere)
// {

// }