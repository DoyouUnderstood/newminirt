#include "../include/minilibx.h"

#define KEY_ESC 53
#define KEY_RIGHT 124
#define KEY_LEFT 123
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_SHRINK_ROTATE 12 // 'q'
#define KEY_SHRINK_SHEAR 13  // 'w'
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_F 3
#define KEY_K 40


//fonction evenement pour quitter avec echap
int handle_keypress(int keysym, t_mlx *mlx)
{
    if (keysym == KEY_ESC)
    {
        mlx_cleanup(mlx); // Nettoie et libère les ressources
        exit(0); // Ferme l'application
    }
    return (0);
}

// fonction pour quitter avec la croix rouge
int close_window(t_mlx *mlx)
{
    exit(0);
    mlx_cleanup(mlx);
    return (0);
}

void apply_transformation_to_sphere(t_sphere *sphere, t_matrix transformation) {
    sphere->transform = multiply_matrices(sphere->transform, transformation);
}

void redraw_scene(t_mlx *mlx, t_matrix transformation) {
    if (mlx == NULL || mlx->ptr == NULL) {
        write(1, "Invalid scene or MLX pointer.\n", 30);
        return;
    }
    if (mlx->img != NULL) {
        mlx_destroy_image(mlx->ptr, mlx->img);
    }
    mlx->img = mlx_new_image(mlx->ptr, mlx->width, mlx->height);
    if (mlx->img == NULL) {
        write(1, "Failed to create image.\n", 24);
        return;
    }
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
    t_sphere sphere;
    sphere.center = point(0, 0, 0);
    sphere.diameter = 1.0;
    sphere.color = (t_color){255, 0, 0};
    sphere.transform = init_matrice_identite();
    apply_transformation_to_sphere(&sphere, transformation);
    throw_ray(mlx, &sphere);
    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}

int handle_key(int keycode, void *param) 
{
    t_mlx *mlx = (t_mlx*)param;
    t_matrix transformation = init_matrice_identite();
    if (keycode == KEY_A) {
        transformation = scaling_matrix(1, 0.5, 1); // Rétrécir le long de l'axe Y
    } else if (keycode == KEY_S) {
        transformation = scaling_matrix(0.5, 1, 1); // Rétrécir le long de l'axe X
    } else if (keycode == KEY_SHRINK_ROTATE) {
        t_matrix rotation = rotation_z(M_PI / 4);
        t_matrix scaling = scaling_matrix(0.5, 1, 1); // Réduire et faire pivoter
        transformation = multiply_matrices(rotation, scaling);
    } else if (keycode == KEY_SHRINK_SHEAR) {
        t_matrix shearing = shearing_matrix(1, 0, 0, 0, 0, 0);
        t_matrix scaling = scaling_matrix(0.5, 1, 1); // Rétrécir et incliner
        transformation = multiply_matrices(shearing, scaling);
    }
    redraw_scene(mlx, transformation);
    return (0);
}

