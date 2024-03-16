#ifndef SHAPE_H
#define SHAPE_H

#include <stdlib.h>
#include <unistd.h>

#include "graphics.h"
#include "mathematique.h"
#include "ray.h"

typedef struct s_sphere 
{
    t_tuple center;
    double diameter;
    t_color color;
    t_matrix transform;
	// t_material material;
} t_sphere;

typedef struct s_intersection
{
    double t[2];
    int count;
}   t_intersection;

// =========== SPHERE =============

t_intersection intersect_sphere(const t_ray *ray, const t_sphere *sphere);
t_sphere create_sphere();

#endif
