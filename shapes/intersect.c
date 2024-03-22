#include "../include/shape.h"

// Fonction pour créer une intersection
t_intersection create_intersection(double t, t_object *object) {
    t_intersection i;
    i.t = t;
    i.object = object;
    return i;
}

// vérifier si la matrice de transformation de l'objet est la matrice identité avant de 
// calculer son inverse. 
// Cela pourrait réduire les calculs inutiles dans les cas où l'objet n'est pas transformé.
// fonction qui appelle les fonctinos d'intersection specifique au object. PEUT ETRE A OPTIMISER
t_intersection* intersect(const t_ray *ray, t_object *object, int* out_count) 
{
    t_ray transformed_ray;

    // s'assurez qu'on a affaire a une sphère.
    if (object->type == SPHERE) {
        // Cast `object->obj` en `t_sphere*` pour accéder à sa matrice de transformation.
        t_sphere* sphere = (t_sphere*)object->obj;

        // Calculez l'inverse de la matrice de transformation de la sphère,
        // peu importe si c'est la matrice identité ou une matrice de transformation complexe.
        t_matrix inverse_transform = matrix_inverse(sphere->transform);
        
        // Appliquez cette transformation inverse au rayon.
        transformed_ray = ray_transform(inverse_transform, *ray);
    } else {
        // Pour tous les autres types d'objets ou si aucune transformation n'est appliquée,
        // considerons le rayon original.
        transformed_ray = *ray;
    }

    // on utilse le rayon transformé pour calculer les intersections.
    switch (object->type) {
        case SPHERE:
            return sphere_intersect(&transformed_ray, object, out_count);
        default:
            *out_count = 0;
            return NULL;
    }
}

// Fonction pour identifier le hit parmi une collection d'intersections
t_intersection* hit(t_intersection* intersections, int count) 
{
    t_intersection* hit = NULL;
    double min_t = DBL_MAX;

    for (int i = 0; i < count; i++) {
        if (intersections[i].t > 0 && intersections[i].t < min_t) {
            hit = &intersections[i];
            min_t = intersections[i].t;
        }
    }

    return (hit);
}
