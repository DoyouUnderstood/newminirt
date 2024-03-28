#include "../include/ray.h"
#include <stdint.h>

t_ray init_ray(t_mlx *mlx, int x, int y, double projection_plane_z) {
    t_tuple camera_position = point_create(0, 0, -5);
    double pixel_world_x = ((double)x / mlx->width - 0.5) * (mlx->width / 100);
    double pixel_world_y = ((double)y / mlx->height - 0.5) * (mlx->height / 100);

    t_tuple pixel_target = point_create(pixel_world_x, -pixel_world_y, projection_plane_z);
    t_ray ray;
    ray.origin = camera_position;
    ray.direction = vector_normalize(tuple_subtract(pixel_target, camera_position));
    return ray;
}

t_color calculate_color(t_intersection *closest_hit, t_ray *ray, t_light *light) {
    if (closest_hit != NULL && closest_hit->object->type == SPHERE) 
    {
        t_sphere* hit_sphere = (t_sphere*)closest_hit->object->obj; // La sphère touchée
        t_tuple hit_point = t_point_position(*ray, closest_hit->t); // Point d'impact
        t_tuple normal = normal_at(hit_sphere, hit_point); // Normal au point d'impact
        t_tuple eye = vector_negate(ray->direction);
        return lighting(&hit_sphere->material, light, &hit_point, &eye, &normal);
    } else {
        return (t_color){0.1, 0.1, 0.1};
    }
}

void draw_pixel(t_mlx *mlx, int x, int y, t_color color) {
    uint32_t rgb_color = color_to_rgb(color.r, color.g, color.b);
    mlx_put_pixel_to_img(mlx, x, y, rgb_color);
}

void ray_throw(t_mlx *mlx, t_sphere *sphere, t_light *light) {
    double projection_plane_z = 7.0;
    t_ray ray;
    for (int y = 0; y < mlx->height; ++y) 
    {
        for (int x = 0; x < mlx->width; ++x) 
        {
            ray = init_ray(mlx, x, y, projection_plane_z);
            int count;
            t_object obj;
            obj.type = SPHERE;
            obj.obj = sphere;
            t_intersection *intersections = intersect(&ray, &obj, &count);
            t_intersection *closest_hit = hit(intersections, count);
            t_color color = calculate_color(closest_hit, &ray, light);
            draw_pixel(mlx, x, y, color);
            if (intersections != NULL) 
                free(intersections);
        }
    }
}
