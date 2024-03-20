#ifndef RAY_H
#define RAY_H

#include "mathematique.h"
#include "minilibx.h"
#include "shape.h"
#include "graphics.h"

typedef struct s_mlx t_mlx;
typedef struct s_sphere t_sphere;
typedef struct s_ray 
{
    t_tuple origin;
    t_tuple direction;
} t_ray;

// =========== RAY ============
t_ray   create_ray(t_tuple origin, t_tuple direction);
t_ray   transform_ray(t_matrix mat, t_ray ray);
void    throw_ray(t_mlx *mlx, t_sphere *sphere, t_light light);

#endif