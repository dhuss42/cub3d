/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:26:59 by maustel           #+#    #+#             */
/*   Updated: 2024/12/19 10:26:59 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_TYPEDEF_H
# define CUB_TYPEDEF_H

# include <stdint.h>
# include <stdbool.h>

typedef struct s_cub	t_cub;

typedef enum e_custom_error
{
	E_ARGS = 107,
	E_EMPTYFILE,
	E_DUPLICATE,
	E_LINECONTENT,
	E_INVALIDNBR,
	E_MALLOC,
	E_MISSING,
	E_FILENAME,
	E_NOMAP,
	E_NEWLINEMAP,
	E_TOOMANYPLAYERS,
	E_NOPLAYER,
	E_OPENMAP,
	E_MLXINIT,
	E_MLXIMG,
	E_MLXIMGTOWIN,
	E_MLXLOADPNG
}				t_custom_error;

typedef struct s_assets
{
	char			*no;	//filename to NO asset
	char			*ea;
	char			*so;
	char			*we;
	uint32_t		c;		//color ceiling
	uint32_t		f;		//color floor
	bool			c_set;
	bool			f_set;
	int				err;
	int				i;
}					t_assets;

/*
	---- how to transform uint32_t (little endian) into single colors ----
	uint8_t red = (nbr_uint32 >> 16) & 0xFF;
	uint8_t green = (nbr_uint32 >> 8) & 0xFF;
	uint8_t blue = nbr_uint32 & 0xFF;
*/

typedef struct s_map
{
	char	**map;
	char	*line;
	bool	is_map;
	bool	is_player;
	int		player_pos[2];
	int		nbr_lines;
	int		line_start;
	int		longest_line;
	int		current_line;
	int		err;
}					t_map;

typedef enum e_dir
{
	X_DIR,
	Y_DIR,
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

typedef struct s_game
{
	t_cub			*cub;
	mlx_t			*mlx;
	mlx_image_t		*map_image;
	mlx_image_t		*wall_image;
	mlx_texture_t	*texture[4];
	t_assets		*ass;
	t_vector		pos_player;
	t_vector		dir_player;
	t_vector		plane;
	t_vector		ray_dir;
	t_point			map_pos;
	t_point			map_size;
	t_point			m_map_size;
	float			camera_x;
	float			player_angle;
	float			first_side_x;
	float			first_side_y;
	float			dist_x;
	float			dist_y;
	float			plane_wall_dist;
	float			wall_x;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				line_start;
	int				line_end;
	int				width;
	int				height;
	int				tex_num;
	int				texture_x;
	uint32_t		colour;
	char			**map;
	char			start_dir;
}	t_game;

typedef struct s_cub
{
	t_map		*mapy;
	t_assets	*assets;
	t_game		*game;
}					t_cub;

#endif
