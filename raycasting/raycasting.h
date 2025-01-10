#ifndef RAYCASTING_H
# define RAYCASTING_H

// #include "../cub.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"

#define WIDTH 1280
#define HEIGHT 640
#define PI 3.14159265358979323846  // Define Pi

//---------------- COLORS --------------//
# define RESET       "\033[0m"
# define BLACK       "\033[30m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

typedef struct s_vector 
{
    float   x;
    float   y;
} t_vector;

typedef struct s_point
{
    int x;
    int y;
} t_point;

typedef struct s_cub
{
    mlx_t       *mlx;
    mlx_image_t *image;
    mlx_image_t *player_image;
    mlx_image_t *dir_image;
    mlx_image_t *drawn_walls;
    mlx_image_t *rays;
    t_vector    pos_player;
    t_vector    dir_player;
    t_vector    plane;
    t_vector    ray_dir;
    t_point     map_pos;
    float       camera_x;
    float       player_angle;
    float       first_side_x;
    float       first_side_y;
    float       dist_x;
    float       dist_y;
    float       plane_wall_dist;
    int         step_x;
    int         step_y;
    int         hit;
    int         side;
    int         line_height;
    int         line_start;
    int         line_end;
    uint32_t   colour;
    char        **map;
    char        start_dir;
} t_cub;

int create_vectors(t_cub *cub);
void    raycaster(t_cub *cub);

void	draw_cell(mlx_image_t *image, int start_x, int start_y, int cell_size, uint32_t color);

// -------helpers---------- //
bool is_player(char c, t_cub *cub);

#endif


