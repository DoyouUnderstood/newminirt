#include "../include/ray.h"
#include <stdint.h>

// Fonction pour initialiser un rayon
t_ray ray_create(t_tuple origin, t_tuple direction) {
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
t_tuple t_point_position(t_ray ray, double t) 
{
    t_tuple displacement = point_multiply(ray.direction, t);
    return (point_add_vector(ray.origin, displacement));
}

// fonction pour transformer un rayon suivant une matrix
t_ray ray_transform(t_matrix mat, t_ray ray) {
    t_ray transformed_ray;
    transformed_ray.origin = matrix_multiply_by_tuple(mat, ray.origin);
    transformed_ray.direction = matrix_multiply_by_tuple(mat, ray.direction);

    return transformed_ray;
}