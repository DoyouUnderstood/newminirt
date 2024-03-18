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

void throw_ray(t_mlx *mlx, t_sphere *sphere) {
    // Position de la caméra
    t_tuple camera_position = point(0, 0, -5);

    // Distance du plan de projection devant la caméra
    double projection_plane_z = 5.0;

    t_ray ray;
    ray.origin = camera_position;

    // Création d'un objet pour la sphère pour utiliser dans l'intersection
    t_object obj;
    obj.type = SPHERE;
    obj.obj = sphere;

    // Taille virtuelle de la toile en espace monde pour simplifier, supposons que chaque unité corresponde à un pixel
    // Cela implique un ajustement selon la taille réelle de votre toile pour maintenir les proportions
    double view_width = (double)mlx->width / 100;
    double view_height = (double)mlx->height / 100;

    for (int y = 0; y < mlx->height; ++y) {
        for (int x = 0; x < mlx->width; ++x) {
            // Calculer la position du pixel dans le plan de projection en espace monde
            double pixel_world_x = ((double)x / mlx->width - 0.5) * view_width;
            double pixel_world_y = ((double)y / mlx->height - 0.5) * view_height;

            // Créer un rayon partant de la caméra vers ce point
            t_tuple pixel_target = point(pixel_world_x, -pixel_world_y, projection_plane_z);
            ray.direction = normalize_vector(subtract_vectors(pixel_target, ray.origin));

            int count;
            t_intersection *intersections = intersect(&ray, &obj, &count);

            if (count > 0) {
                put_pixel_to_img(mlx, x, y, 0xFF0000); // Dessiner en rouge si intersection
            } else {
                put_pixel_to_img(mlx, x, y, 0x000000); // Dessiner en noir si pas d'intersection
            }

            if (intersections != NULL) {
                free(intersections);
            }
        }
    }
}




#define UNIT_TEST 0
int main(int argc, char *argv[]) 
{
    (void)argc;
    (void)argv;
    if (UNIT_TEST == 1)
        unit_test();

    t_mlx *mlx = mlx_init_and_create_window(860, 600, "minirt");
   if (!mlx) return 1; // Gestion d'erreur basique
    mlx_create_image(mlx);

    // Création et configuration d'une sphère
    t_sphere sphere;
    sphere.center = point(0, 0, 0);  // Centre de la sphère à l'origine
    sphere.diameter = 1.0;           // Diamètre de la sphère
    sphere.color = (t_color){255, 0, 0}; // Couleur rouge (ce champ est illustratif, adaptez selon votre structure)
    sphere.transform = init_matrice_identite(); // Transformation par défaut

    // Lancer des rayons sur la sphère et dessiner le résultat
    throw_ray(mlx, &sphere);

    // Affichage de l'image à l'écran
    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);

    // Hook pour gérer la fermeture de la fenêtre
    mlx_hook(mlx->win, 17, 0L, close_window, mlx);

    // Boucle principale de MiniLibX pour gérer les événements
    mlx_loop(mlx->ptr);

    // Libération des ressources avant de quitter
    mlx_destroy_window(mlx->ptr, mlx->win);
    free(mlx);

    return 0;
}