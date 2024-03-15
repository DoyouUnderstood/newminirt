#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef struct s_color
{
	double r;
	double g;
	double b;
}					t_color;

t_color color_add(t_color c1, t_color c2);
t_color color_multiply(t_color c1, t_color c2);
t_color color_multiply_alternativ(t_color c1, t_color c2);

#endif