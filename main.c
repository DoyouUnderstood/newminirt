#include "include/main.h"

void error_exit(char *error_msg)
{
    printf("%s\n", error_msg);
    exit(1);
}


void unit_test()
{   
    struct criterion_test_set *tests = criterion_initialize();
    int result = criterion_run_all_tests(tests);
    criterion_finalize(tests);
    (void)result;
    error_exit("TEST FONCTION");
}


void    mlx_initialisation(void)
{
    t_mlx *mlx = mlx_init_and_create_window(860, 600, "minirt");
    t_sphere *sphere;
    t_light *light;
    if (!mlx) 
        error_exit("erreur initialisation mlx\n");
    mlx_create_image(mlx);
    
    sphere = sphere_create();
    light = light_create((t_color){1, 1, 1}, point_create(-10 , 10, -10));

    ray_throw(mlx, sphere, light);
    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
    mlx_hook(mlx->win, 17, 0L, mlx_event_close_win, mlx);
    mlx_hook(mlx->win, 2, 1L<<0, mlx_event_handle_key, mlx);
    mlx_loop(mlx->ptr);
    mlx_destroy_window(mlx->ptr, mlx->win);
    free(mlx);

}

#define UNIT_TEST 1

int main(int argc, char *argv[]) 
{
    (void)argc;
    (void)argv;
    if (UNIT_TEST == 1)
        unit_test();
    else
        mlx_initialisation();
    
    return (0);
}