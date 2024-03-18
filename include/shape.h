#ifndef SHAPE_H
#define SHAPE_H

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

#include "main.h"
#include "graphics.h"
#include "mathematique.h"
#include "ray.h"

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	INVALID_TYPE = -1,
}					t_obj_type;

 typedef struct s_object
{
	t_obj_type		type;
	void			*obj;
	struct s_object	*next;
}					t_object;

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
    double t;
    t_object *object; // Pointeur vers l'objet intersecté
}   t_intersection;

// =========== SPHERE =============

t_intersection* intersect(const t_ray *ray, t_object *object, int* out_count);
t_intersection* sphere_intersect(const t_ray *ray, t_object *object, int* out_count);
t_sphere		create_sphere();
t_object*		create_object_for_sphere(const t_sphere* sphere);
void 			set_transform(t_sphere *sphere, t_matrix new_transform);

// ============ INTERSECT ==============

t_intersection create_intersection(double t, t_object *object);
t_intersection* intersect(const t_ray *ray, t_object *object, int* out_count);
t_intersection* hit(t_intersection* intersections, int count);

#endif
