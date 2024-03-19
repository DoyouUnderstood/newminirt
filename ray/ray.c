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

void throw_ray(t_mlx *mlx, t_sphere *sphere) 
{
    t_tuple camera_position = point(0, 0, -5);
    // Distance du plan de projection devant la caméra
    double projection_plane_z = 7.0;
    t_ray ray;
    ray.origin = camera_position;
    t_object obj;
    obj.type = SPHERE;
    obj.obj = sphere;

    // Taille virtuelle de la toile en espace monde pour simplifier, supposons que chaque unité corresponde à un pixel
    // Cela implique un ajustement selon la taille réelle de votre toile pour maintenir les proportions
    double view_width = (double)mlx->width / 100;
    double view_height = (double)mlx->height / 100;

    for (int y = 0; y < mlx->height; ++y) {
        for (int x = 0; x < mlx->width; ++x) {
            // Calculer la position du pixel dans le plan de projection en espace monde
            double pixel_world_x = ((double)x / mlx->width - 0.5) * view_width;
            double pixel_world_y = ((double)y / mlx->height - 0.5) * view_height;

            // Créer un rayon partant de la caméra vers ce point
            t_tuple pixel_target = point(pixel_world_x, -pixel_world_y, projection_plane_z);
            ray.direction = normalize_vector(subtract_vectors(pixel_target, ray.origin));

            int count;
            t_intersection *intersections = intersect(&ray, &obj, &count);
            if (count > 0) 
                put_pixel_to_img(mlx, x, y, 0xFF0000);
            else
                put_pixel_to_img(mlx, x, y, 0x000000);
            if (intersections != NULL)
                free(intersections);
        }
    }
}

