
NAME = miniRT

LIBFT_DIR = lib/libft
FT_PRINTF_DIR = lib/ft_printf
GNL_DIR = lib/GNL
MLX_DIR = lib/mlx_linux

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# / pour compiler sous Mac, rajouter ceci a mlx_flags ==> -framework OpenGL -framework AppKit

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
CRITERION_FLAGS = -lcriterion
INC_FLAGS = -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -lm

TEST_SRCS = unit_test/test_intersection_sphere.c unit_test/test_tracking_intersection.c \
		unit_test/test_hit.c unit_test/test_transorm_ray_and_sphere.c unit_test/test_normat_at.c \
		unit_test/test_reflect.c unit_test/test_lightning.c

SRCS = main.c \
      graphics/color.c \
      maths/determinant_cofacteur.c \
      maths/matrix_operation.c \
      maths/matrix_transforms.c \
      maths/point.c \
      maths/vect.c \
      mlx/event.c \
      mlx/mlx.c \
      ray/ray.c \
      shapes/sphere.c \
	  shapes/intersect.c \
	  maths/sphere_operation.c \
	  maths/normal.c \
	  graphics/material.c \
	  graphics/lightning.c \
	  maths/utils.c \
	  maths/tuple.c \
	  memory/memory.c


OBJ = $(SRCS:.c=.o)

TEST_OBJ = $(TEST_SRCS:.c=.o)

LIBS = $(LIBFT_DIR)/libft.a $(FT_PRINTF_DIR)/libftprintf.a $(GNL_DIR)/libgnl.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) -o $(NAME) $(LIBS) $(MLX_FLAGS) $(INC_FLAGS) $(CRITERION_FLAGS)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(FT_PRINTF_DIR)/libftprintf.a:
	make -C $(FT_PRINTF_DIR)

$(GNL_DIR)/libgnl.a:
	make -C $(GNL_DIR)


test: $(TEST_SRCS) $(LIBS)
	clang $(CFLAGS) -o test_$(NAME) $(TEST_SRCS) $(OBJ) $(LIBS) $(MLX_FLAGS) $(INC_FLAGS) $(CRITERION_FLAGS)
	./test_$(NAME)


# Règle pour nettoyer les objets
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
