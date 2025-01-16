#ifndef RAYCASTING_H
# define RAYCASTING_H

// #include "../cub.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"

#define WIDTH 1240
#define HEIGHT 720
#define PI 3.14159265358979323846  // Define Pi

//---------------- COLORS --------------//
# define RESET	   "\033[0m"
# define BLACK	   "\033[30m"
# define RED		 "\033[31m"
# define GREEN	   "\033[32m"
# define YELLOW	  "\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	 "\033[35m"
# define CYAN		"\033[36m"
# define WHITE	   "\033[37m"

typedef enum e_key
{
	W,
	S,
	A,
	D,
} t_key;

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
	mlx_t		*mlx;
	mlx_image_t	*map_image;
	mlx_image_t	*wall_image;
	mlx_image_t	*player_image;
	mlx_image_t	*dir_image;
	mlx_image_t	*rays;
	t_vector	pos_player;
	t_vector	dir_player;
	t_vector	plane;
	t_vector	ray_dir;
	t_vector	buffer;
	t_point		map_pos;
	t_point		map_size;
	float		camera_x;
	float		player_angle;
	float		first_side_x;
	float		first_side_y;
	float		dist_x;
	float		dist_y;
	float		plane_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			line_start;
	int			line_end;
	int			width;
	int			height;
	int			cell_size;
	uint32_t	colour;
	char		**map;
	char		start_dir;
	bool		bottom;
} t_cub;

//-init-//
void	init_win_imgs(t_cub *cub);

//-mini_map-//
void	mini_map(t_cub *cub);
void	draw_mini_map(t_cub *cub);
int		create_vectors(t_cub *cub);

//-raycasting-//
void	raycaster(t_cub *cub);

//-drawing-//
void	draw_player(t_cub *cub);
void	draw_cell(mlx_image_t *image, int start_x, int start_y, int cell_size, uint32_t color, t_cub *cub);
void	new_image(mlx_t *mlx, mlx_image_t **image, uint32_t width, uint32_t height);
void	draw_direction(t_cub *cub, float dir_x, float dir_y);

//-input-//
void	ft_key_hook(void* param);

// -------helpers---------- //
bool	is_player(char c, t_cub *cub);
void	get_map_size(t_cub *cub);

#endif


