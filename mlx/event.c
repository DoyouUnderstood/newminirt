#include "../include/minilibx.h"

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
