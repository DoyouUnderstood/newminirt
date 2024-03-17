NAME = miniRT

LIBFT_DIR = lib/libft
FT_PRINTF_DIR = lib/ft_printf
GNL_DIR = lib/GNL
MLX_DIR = lib/mlx_linux

CC = gcc
CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -L$(MLX_DIR) -lmlx
INC_FLAGS = -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -lXext -lX11 -lm -lbsd
CRITERION_FLAGS = -lcriterion

# Séparez les fichiers de test des fichiers sources principaux si possible
TEST_SRCS = unit_test/test_intersection_sphere.c unit_test/test_tracking_intersection.c
# Vous pouvez ajouter ou supprimer des fichiers de test de cette variable

SRC = main.c \
      graphics/color.c \
      maths/determinant_cofacteur.c \
      maths/matrix_operation.c \
      maths/matrix_transforms.c \
      maths/point.c \
      maths/vect.c \
      mlx/event.c \
      mlx/mlx.c \
      ray/ray.c \
      shapes/sphere.c 

OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRCS:.c=.o)

LIBS = $(LIBFT_DIR)/libft.a $(FT_PRINTF_DIR)/libftprintf.a $(GNL_DIR)/libgnl.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
		$(CC) $(OBJ) -o $(NAME) $(LIBS) $(MLX_FLAGS) $(INC_FLAGS) $(CRITERION_FLAGS)

# Ajoutez ici les dépendances pour vos bibliothèques si elles ne sont pas déjà incluses
$(LIBFT_DIR)/libft.a:
		make -C $(LIBFT_DIR)

$(FT_PRINTF_DIR)/libftprintf.a:
		make -C $(FT_PRINTF_DIR)

$(GNL_DIR)/libgnl.a:
		make -C $(GNL_DIR)

# Cible pour compiler et exécuter les tests
test: $(TEST_OBJ) $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(TEST_OBJ) -o test_$(NAME) $(LIBS) $(MLX_FLAGS) $(INC_FLAGS) $(CRITERION_FLAGS)
		./test_$(NAME)


clean:
		rm -f $(OBJ) # $(TEST_OBJ)
		make -C $(LIBFT_DIR) clean
		make -C $(FT_PRINTF_DIR) clean
		make -C $(GNL_DIR) clean

fclean: clean
		rm -f $(NAME) test_$(NAME)
		make -C $(LIBFT_DIR) fclean
		make -C $(FT_PRINTF_DIR) fclean
		make -C $(GNL_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test
