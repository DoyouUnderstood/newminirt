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

// fonction pour transformer un rayon suivant une matrix
t_ray transform_ray(t_matrix mat, t_ray ray) {
    t_ray transformed_ray;
    transformed_ray.origin = multiply_matrix_by_tuple(mat, ray.origin);
    transformed_ray.direction = multiply_matrix_by_tuple(mat, ray.direction);

    return transformed_ray;
}

// Convertit une couleur du format flottant (dans l'intervalle [0,1] pour chaque composante) vers un format RGB entier sur 3 octets.
uint32_t color_to_rgb(float red, float green, float blue) {
    // Assurez-vous que les valeurs sont dans l'intervalle [0,1]
    red = fmax(0, fmin(red, 1));
    green = fmax(0, fmin(green, 1));
    blue = fmax(0, fmin(blue, 1));

    // Convertissez les valeurs flottantes en valeurs entières dans l'intervalle [0,255]
    uint8_t r = (uint8_t)(red * 255);
    uint8_t g = (uint8_t)(green * 255);
    uint8_t b = (uint8_t)(blue * 255);

    // Combine les composantes en une seule valeur RGB
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

void throw_ray(t_mlx *mlx, t_sphere *sphere, t_light light) 
{
    // (void)light;
    t_tuple camera_position = point(0, 0, -5);
    double projection_plane_z = 7.0;
    t_ray ray;
    ray.origin = camera_position;

    // Supposons que default_material est déjà appliqué à la sphère lors de sa création ou ailleurs

    for (int y = 0; y < mlx->height; ++y) 
    {
        for (int x = 0; x < mlx->width; ++x)
        {
            double pixel_world_x = ((double)x / mlx->width - 0.5) * (mlx->width / 100);
            double pixel_world_y = ((double)y / mlx->height - 0.5) * (mlx->height / 100);

            t_tuple pixel_target = point(pixel_world_x, -pixel_world_y, projection_plane_z);
            ray.direction = normalize_vector(subtract_vectors(pixel_target, ray.origin));

            int count;
            t_object obj; // Créez un objet temporaire pour la sphère, pas besoin de pointeur ici si vous passez par valeur
            obj.type = SPHERE;
            obj.obj = sphere;
            t_intersection *intersections = intersect(&ray, &obj, &count);

            t_intersection *closest_hit = hit(intersections, count);
            if (closest_hit != NULL && closest_hit->object->type == SPHERE) 
            {
                t_sphere* hit_sphere = (t_sphere*)closest_hit->object->obj; // La sphère touchée
                t_tuple hit_point = position(ray, closest_hit->t); // Point d'impact
                t_tuple normal = normal_at(hit_sphere, hit_point); // Normal au point d'impact
                t_tuple eye = vector_negate(ray.direction); // Vecteur oeil
                light.intensity.r = 1.0;
                light.intensity.g = 1.0;
                light.intensity.b = 1.0;

                printf("Light Pos: (%f, %f, %f), Intensity: (%f, %f, %f)\n", light.pos.x, light.pos.y, light.pos.z, light.intensity.r, light.intensity.g, light.intensity.b);
                printf("Hit Point: (%f, %f, %f)\n", hit_point.x, hit_point.y, hit_point.z);
                printf("Normal: (%f, %f, %f)\n", normal.x, normal.y, normal.z);
                printf("Eye: (%f, %f, %f)\n", eye.x, eye.y, eye.z);

                t_color color = lighting(hit_sphere->material, light, hit_point, eye, normal);
                // printf("%f\n %f\n %f\n", color.r, color.g, color.b);
                uint32_t rgb_color = color_to_rgb(color.r, color.g, color.b);
                put_pixel_to_img(mlx, x, y, rgb_color);
            } else {
                put_pixel_to_img(mlx, x, y, 0x077770);
            }

            if (intersections != NULL) {
                free(intersections);
            }
        }
    }
}



