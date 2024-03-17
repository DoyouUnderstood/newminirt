#include "../include/shape.h"

// fonction qui cree une sphere.
t_sphere create_sphere() 
{
    t_sphere sphere;
    sphere.center = point(0, 0, 0);
    sphere.diameter = 1.0;
    sphere.color = (t_color){.r = 255, .g = 255, .b = 255};
    sphere.transform = init_matrice_identite();

    return (sphere);
}

// Calcule les coefficients 'a', 'b', et 'c' pour l'équation quadratique d'intersection.
void calculate_abc(const t_ray *ray, const t_sphere *sphere, double *a, double *b, double *c) {
    t_tuple sphere_to_ray = subtract_vectors(ray->origin, sphere->center);
    *a = dot_product(ray->direction, ray->direction);
    *b = 2 * dot_product(ray->direction, sphere_to_ray);
    *c = dot_product(sphere_to_ray, sphere_to_ray) - pow(sphere->diameter, 2);
}

// Calcule le discriminant à partir des coefficients 'a', 'b', et 'c'.
double calculate_discriminant(double a, double b, double c) {
    return b * b - 4 * a * c;
}

// Crée un nouvel objet t_object pour une sphère
t_object* create_object_for_sphere(const t_sphere* sphere) {
    t_object* obj = malloc(sizeof(t_object));
    if (obj == NULL) {
        error_exit("error malloc t_object sphere.c");
    }
    obj->type = SPHERE;
    obj->obj = (void*)sphere;
    obj->next = NULL;
    return obj;
}

// Fonction pour calculer l'intersection d'un rayon avec une sphère.
t_intersection* sphere_intersect(const t_ray *ray, t_object *object, int* out_count) 
{
    t_sphere* sphere = (t_sphere*)object->obj;
    
    double a, b, c;
    calculate_abc(ray, sphere, &a, &b, &c);
    double discriminant = calculate_discriminant(a, b, c);
    
    t_intersection* intersections = NULL;
    *out_count = 0;
    
    intersections = malloc(sizeof(t_intersection) * 2);
    if (intersections == NULL) {
        return NULL;
    }

    if (discriminant >= 0) {
        double sqrt_discriminant = sqrt(discriminant);
        double t1 = (-b - sqrt_discriminant) / (2 * a);
        double t2 = discriminant == 0 ? t1 : (-b + sqrt_discriminant) / (2 * a);

        intersections[0].t = fmin(t1, t2);
        intersections[1].t = fmax(t1, t2);
        *out_count = 2;

        for (int i = 0; i < *out_count; i++) {
            intersections[i].object = object;
        }
    } else {
        free(intersections);
        intersections = NULL;
    }

    return (intersections);
}

// fonction qui appelle les fonctinos d'intersection specifique au object.
t_intersection* intersect(const t_ray *ray, t_object *object, int* out_count) 
{
    switch (object->type) 
    {
        case SPHERE:
            return sphere_intersect(ray, object, out_count);
        default:
            *out_count = 0;
            return NULL;
    }
}





