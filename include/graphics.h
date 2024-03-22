#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "mathematique.h"

typedef struct s_color
{
	double r;
	double g;
	double b;
}					t_color;

typedef struct s_light
{
	t_color intensity;
	t_tuple pos;
}	t_light;

typedef struct s_material
{
	t_color color;
	double ambient;
	double diffuse;
	double specular;
	double shininess;
}	t_material;


t_color color_add(t_color c1, t_color c2);
t_color color_multiply(t_color c1, t_color c2);
t_color color_multiply_alternativ(t_color c1, t_color c2);
t_color color_multiply_scalar(t_color c, double scalar);

t_light light_create(t_color color, t_tuple position);

t_material material_create_default();

t_color lighting(t_material material, t_light light, t_tuple position, t_tuple eyev, t_tuple normalv);
#endif