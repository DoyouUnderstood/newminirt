#include "../include/main.h"

#include "../include/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include <math.h>

t_camera camera(int hsize, int vsize, float fov) {
    t_camera cam;
    cam.hsize = hsize;
    cam.vsize = vsize;
    cam.fov = fov;
    cam.transform = matrix_init_identity();

    float half_view = tan(cam.fov / 2.0);
    float aspect = (float)cam.hsize / (float)cam.vsize;

    if (aspect >= 1) {
        cam.half_width = half_view;
        cam.half_height = half_view / aspect;
    } else {
        cam.half_width = half_view * aspect;
        cam.half_height = half_view;
    }

    cam.pixel_size = (cam.half_width * 2) / cam.hsize;

    return cam;
}

t_ray ray_for_pixel(const t_camera *camera, int px, int py) {
    // Calcul des offsets du centre du pixel
    double xoffset = (px + 0.5) * camera->pixel_size;
    double yoffset = (py + 0.5) * camera->pixel_size;

    // Coordonnées du pixel dans l'espace du monde
    double world_x = camera->half_width - xoffset;
    double world_y = camera->half_height - yoffset;

    // Transformation du point du pixel et de l'origine
    t_tuple pixel = matrix_multiply_by_tuple(matrix_inverse(camera->transform), point_create(world_x, world_y, -1));
    t_tuple origin = matrix_multiply_by_tuple(matrix_inverse(camera->transform), point_create(0, 0, 0));
    t_tuple direction = vector_normalize(tuple_subtract(pixel, origin));

    // Création et retour du rayon
    t_ray ray = {origin, direction};
    return ray;
}


