#include "../include/shape.h"

// Calcule les coefficients 'a', 'b', et 'c' pour l'équation quadratique d'intersection.
void calculate_abc(const t_ray *ray, const t_sphere *sphere, double *a, double *b, double *c) {
    t_tuple sphere_to_ray = tuple_subtract(ray->origin, sphere->center);
    *a = vector_dot(ray->direction, ray->direction);
    *b = 2 * vector_dot(ray->direction, sphere_to_ray);
    *c = vector_dot(sphere_to_ray, sphere_to_ray) - pow(sphere->diameter, 2);
}

// Calcule le discriminant à partir des coefficients 'a', 'b', et 'c'.
double calculate_discriminant(double a, double b, double c) 
{
    return b * b - 4 * a * c;
}

// Calcule les points d'intersection à partir du discriminant, 'a', 'b', et met à jour `xs`.
void calculate_intersections(double discriminant, double a, double b, t_intersection *xs) {
    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2 * a);
    if (discriminant > 0) 
    {
        double t2 = (-b + sqrt_discriminant) / (2 * a);
        xs->t[0] = fmin(t1, t2);
        xs->t[1] = fmax(t1, t2);
        xs->count = 2;
    } else {
        xs->t[0] = t1;
        xs->t[1] = t1;
        xs->count = 2;
    }
}

// Fonction principale pour calculer l'intersection d'un rayon avec une sphère.
t_intersection intersect_sphere(const t_ray *ray, const t_sphere *sphere) {
    double a, b, c;
    calculate_abc(ray, sphere, &a, &b, &c);
    double discriminant = calculate_discriminant(a, b, c);
    
    t_intersection xs = { .count = 0 };
    if (discriminant >= 0) 
    {
        calculate_intersections(discriminant, a, b, &xs);
    }
    return (xs);
}