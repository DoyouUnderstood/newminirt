#ifndef RAY_H
#define RAY_H

#include "mathematique.h"


typedef struct s_ray {
    t_tuple origin;
    t_tuple direction;
} t_ray;


t_ray create_ray(t_tuple origin, t_tuple direction);
t_ray transform_ray(t_matrix mat, t_ray ray);

#endif 