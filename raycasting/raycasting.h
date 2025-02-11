/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:29:29 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/11 10:16:19 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"
# include "../cub.h"

# define WIDTH 1440
# define HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define PI 3.14159265358979323846  // Define Pi

//---------------- COLORS --------------//
# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

typedef enum e_dir
{
	X_DIR,
	Y_DIR,
	DIAGONAL,
}	t_dir;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_mini_map
{
	int	render_distance;
	int	min_x;
	int	min_y;
	int	max_x;
	int	max_y;
	int	pos_player_mm_x;
	int	pos_player_mm_y;
}	t_mini_map;

typedef struct s_player_map
{
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;
	float	x;
	float	y;
	float	corners[4][2];
	float	half_size;
	float	perp_x;
	float	perp_y;
}	t_player_map;

typedef struct s_game
{
	t_cub		*cub;
	mlx_t		*mlx;
	mlx_image_t	*map_image;
	mlx_image_t	*wall_image;
	mlx_texture_t	*texture[4];
	t_assets	*ass;
	t_vector	pos_player;
	t_vector	dir_player;
	t_vector	plane;
	t_vector	ray_dir;
	t_point		map_pos;
	t_point		map_size;
	t_point		m_map_size;
	t_mini_map	mini_map;
	float		camera_x;
	float		player_angle;
	float		first_side_x;
	float		first_side_y;
	float		dist_x;
	float		dist_y;
	float		plane_wall_dist;
	float		check_buffer;
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
	int			tex_num;
	int			texture_x;
	float		wall_x;
	uint32_t	colour;
	uint32_t	**buffer;
	char		**map;
	char		start_dir;
	bool		bottom;
	bool		bonus;
}	t_game;

//-init-//
void	rendering(t_cub *cub);
void	init_win_imgs(t_game *game);
int		set_player(t_game *game);
bool	is_player(char c, t_game *game);

//-mini_map-//
void	mini_map(t_game *game);
void	mini_map_bonus(t_game *game);
void	mini_map_size_bonus(t_game *game);
void	draw_mini_map(t_game *game);
void	rotable_player(t_game *game);

//-drawing-//
void	draw_player(t_game *game);
void	draw_cell(t_game *game, int start_x, int start_y, uint32_t color);
void	draw_direction(t_game *game, float dir_x, float dir_y);

//-raycasting-//
void	raycaster(t_game *game);
void	rays(t_game *game, int x);
void	distance_to_first_side(t_game *g);
void	dda(t_game *game);
void	plane_to_wall_distance(t_game *game);
void	calculate_line_height(t_game *game);
void	exact_hit_point(t_game *game);
void	scale_to_texture_width(t_game *game);
void	loop_y_axis(t_game *game, int x);

//-movement-//
void	ft_key_hook(void *param);
void	two_keys_pressed(t_game *game, float *speed);
int		is_coliding(t_game *game, float x, float y);
void	is_side_dir(t_game *game, int sideways, float *move_x, float *move_y);

#endif
