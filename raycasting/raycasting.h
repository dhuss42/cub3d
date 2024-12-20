#ifndef RAYCASTING_H
# define RAYCASTING_H

// #include "../cub.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"

#define WIDTH 512
#define HEIGHT 512

typedef struct s_vector 
{
    float   x;
    float   y;
} t_vector;

typedef struct s_cub
{
    mlx_t       *mlx;
    mlx_image_t *image;
    t_vector    pos_player;
    t_vector    dir_player;
    float       player_angle;
    char        **map;
} t_cub;

int create_vectors(t_cub *cub);

#endif


