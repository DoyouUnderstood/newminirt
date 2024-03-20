#include "../include/graphics.h"

// fonction pour ajouter des couleurs.
t_color color_add(t_color c1, t_color c2) 
{
    t_color result;

    result.r = c1.r + c2.r;
    result.g = c1.g + c2.g;
    result.b = c1.b + c2.b;
    if (result.r > 255)
        result.r = 255;
    if (result.g > 255)
        result.g = 255;
    if (result.b > 255)
        result.b = 255;
    return result;
}

// fonction pour multiplication de deux couleurs
t_color color_multiply(t_color c1, t_color c2) 
{
    t_color result;
    result.r = (c1.r * c2.r) / 255.0;
    result.g = (c1.g * c2.g) / 255.0;
    result.b = (c1.b * c2.b) / 255.0;
    return result;
}

/// fonction alternative pour la multiplication de couleurs.
t_color color_multiply_alternativ(t_color c1, t_color c2) 
{
    t_color result;
    result.r = (c1.r / 255.0) * (c2.r / 255.0) * 255;
    result.g = (c1.g / 255.0) * (c2.g / 255.0) * 255;
    result.b = (c1.b / 255.0) * (c2.b / 255.0) * 255;
    return result;
}

t_light create_light(t_color color, t_tuple position)
{
    t_light light; 

    light.intensity = color;
    light.pos = position;
    return (light);
}

// Fonction pour multiplier une couleur par un scalaire.
t_color color_multiply_scalar(t_color c, double scalar) {
    t_color result;

    result.r = c.r * scalar;
    result.g = c.g * scalar;
    result.b = c.b * scalar;

    return result;
}
