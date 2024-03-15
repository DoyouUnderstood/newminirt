#ifndef MLX_H
#define MLX_H

#include "main.h"
typedef struct s_mlx
{
    void    *ptr;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}               t_mlx;

// ============= FONCTION MLX ================

void    put_pixel_to_img(t_mlx *mlx, int x, int y, int color);
int     mlx_create_image(t_mlx *mlx);
t_mlx   *mlx_init_and_create_window(int width, int height, char *title);
void    mlx_cleanup(t_mlx *mlx);

#endif

