/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:37:08 by maustel           #+#    #+#             */
/*   Updated: 2024/12/18 16:37:08 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "MLX42/include/MLX42/MLX42.h"
# include "cub_typedef.h"
# include "./libft/libft.h"

# define WIDTH 1440
# define HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define PI 3.14159265358979323846

# include <stdio.h>
# include <errno.h>
# include <math.h>

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

/*---------------- ERROR_FREE ----------------*/
void		print_error_free_exit(t_custom_error err, t_cub *cub, char *str);
void		print_error(t_custom_error err, int *err_msg, char *str);
void		free_cub(t_cub *cub);
void		free_double(char **to_free);
void		free_exit(int err, t_cub *cub);
void		free_pngs(t_game *game);
void    	free_mlx(t_game *game, t_custom_error err, int ex);

/*---------------- PARSER -----------------*/
void		parser(char *cub_file, t_cub *cub);
int			is_asset(char *line, t_assets *assets);
int			is_color(char *line, t_assets *assets);
int			is_map(char *line, t_cub *cub);
void		check_rest_line(t_assets *assets, char *line);
uint32_t	color_to_uint32(t_assets *assets, char *line);
void		get_map(char *cub_file, t_cub *cub);
void		check_content(t_cub *cub);
void		check_filename_valid(t_cub *cub, char *path);
void		check_filepath_valid(t_cub *cub, char *file_path);
bool		non_valid_char_map(char c);
void		check_map_valid(int i, int j, t_cub *cub, char **map);
char		**cpy_map(char **map_2d, t_cub *cub);
void		floodfill(char **map, t_cub *cub, int x, int y);
void		check_edge(char **map, t_cub *cub, int x, int y);
void		cut_newlines_map_end(char **map);

/*---------------- INIT WINDOW AND PLAYER -----------------*/
void		rendering(t_cub *cub);
void		init_win_imgs(t_game *game);
int			set_player(t_game *game);
bool		is_player(char c, t_game *game);

/*---------------- DRAWING -----------------*/
void		draw_player(t_game *game);
void		draw_cell(t_game *game, int start_x, int start_y, uint32_t color);
void		draw_direction(t_game *game, float dir_x, float dir_y);
void		draw_rotable_player(t_game *game, t_player_map *pm);

/*---------------- RAYCASTING -----------------*/
void		raycaster(t_game *game);
void		rays(t_game *game, int x);
void		distance_to_first_side(t_game *g);
void		dda(t_game *game);
void		plane_to_wall_distance(t_game *game);
void		calculate_line_height(t_game *game);
void		exact_hit_point(t_game *game);
void		scale_to_texture_width(t_game *game);
void		loop_y_axis(t_game *game, int x);

/*---------------- INPUT-----------------*/
void		ft_key_hook(void *param);
void		two_keys_pressed(t_game *game, float *speed);
int			is_coliding(t_game *game, float x, float y);
void		side_dir(t_game *game, int sideways, float *move_x, float *move_y);

#endif
