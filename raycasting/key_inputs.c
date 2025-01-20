/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:08:40 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/20 10:20:50 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// saves the previous direction.x so it can be used after the direction of x is updated
// the direction vector is updated with the formula
//	x' = x * cos(angle) - y * sin(angle)
//	y' = x * sin(angle) + y * cos(angle)
// then the camera plane is updated according to the same principle keeping it perpendicular to the direction vector
void	rotation(t_cub *cub, float angle)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = cub->dir_player.x;
	cub->dir_player.x = cub->dir_player.x * cos(angle) - cub->dir_player.y * sin(angle);
	cub->dir_player.y = old_dir_x * sin(angle) + cub->dir_player.y * cos(angle);

	old_plane_x = cub->plane.x;
	cub->plane.x = cub->plane.x * cos(angle) - cub->plane.y * sin(angle);
	cub->plane.y = old_plane_x * sin(angle) + cub->plane.y * cos(angle);
}

// determines in which direction the buffer should be added based on the passed speed
// negative speed means moving backwards
void	get_buffer_dir(float speed, float *buffer_dir)
{
	float	buffer;

	buffer = 0.1;
	if (speed > 0)
		*buffer_dir = buffer;
	else
		*buffer_dir = -buffer;
}

// sets move_x/y to perpundicular to player direction vector
void	is_side_dir(t_cub *cub, int sideways, float *move_x, float *move_y)
{
	if (sideways)
	{
		*move_x = cub->dir_player.y;
		*move_y = -cub->dir_player.x;
	}
	else
	{
		*move_x = cub->dir_player.x;
		*move_y = cub->dir_player.y;
	}
}

// checks if next move in x/y direction is valid, prevents segfault
int	is_within_bounds(t_cub *cub, float x, float y)
{
	return (x >= 0 && x < cub->map_size.x && y >= 0 && y < cub->map_size.y);
}

// updates the player position according to the passed direction
// Also updates the player position on the minimap
void	update_position(t_cub *cub, float next_x, float next_y, int dir)
{
	if (dir == DIAGONAL)
	{
		cub->pos_player.x = next_x;
		cub->pos_player.y = next_y;
		cub->player_image->instances[0].x = cub->pos_player.x * cub->cell_size;
		cub->player_image->instances[0].y = cub->pos_player.y * cub->cell_size;
	}
	else if (dir == X_DIR)
	{
		cub->pos_player.x = next_x;
		cub->player_image->instances[0].x = cub->pos_player.x * cub->cell_size;
	}
	else if (dir == Y_DIR)
	{
		cub->pos_player.y = next_y;
		cub->player_image->instances[0].y = cub->pos_player.y * cub->cell_size;
	}
}

void	normalise(float *move_x, float *move_y)
{
	float	vector_len;

	vector_len = sqrt(*move_x * *move_x + *move_y * *move_y);
	if (vector_len > 0)
	{
		*move_x /= vector_len;
		*move_y /= vector_len;
	}
}

// checks if the next cell is a wall, if not then the player is moved according to the pressed key and passed speed
// moves the player on the minimap in corresponding pixel distance
//	-> buffer acts as a small buffer zone between player and wall
void	movement(t_cub *cub, float speed, int sideways) // -0.07, 1
{
	float	next_x;
	float	next_y;
	float	move_x;
	float	move_y;
	float	check_buffer;

	check_buffer = 0;
	get_buffer_dir(speed, &check_buffer);
	is_side_dir(cub, sideways, &move_x, &move_y);
	normalise(&move_x, &move_y);
	next_x = cub->pos_player.x + move_x * speed;
	next_y = cub->pos_player.y + move_y * speed;
	if (!is_within_bounds(cub, next_x, cub->pos_player.y) || !is_within_bounds(cub, cub->pos_player.x, next_y))
		return ;
	// printf(YELLOW"cub->player_image->instances[0].y / cub->cell_size + cub->cell_size / 2 %d\n"WHITE, (cub->player_image->instances[0].y + cub->cell_size / 2) / cub->cell_size);
	// printf(YELLOW"cub->player_image->instances[0].x / cub->cell_size + cub->cell_size / 2 %d\n"WHITE, (cub->player_image->instances[0].x + cub->cell_size / 2) / cub->cell_size);
	if (cub->map[(int)(next_y + move_y * check_buffer)][(int)(next_x + move_x * check_buffer)] != '1' /* && cub->map[(cub->player_image->instances[0].y + cub->cell_size / 2) / cub->cell_size][(cub->player_image->instances[0].x + cub->cell_size / 2) / cub->cell_size] != '1' */)
		update_position(cub, next_x, next_y, DIAGONAL);
	else
	{
		if (cub->map[(int)cub->pos_player.y][(int)(next_x + move_x * check_buffer)] != '1' /* && cub->map[(cub->player_image->instances[0].y + cub->cell_size / 2) / cub->cell_size][(cub->player_image->instances[0].x + cub->cell_size / 2) / cub->cell_size] != '1' */)
			update_position(cub, next_x, next_y, X_DIR);
		if (cub->map[(int)(next_y + move_y * check_buffer)][(int)cub->pos_player.x] != '1' /* && cub->map[(cub->player_image->instances[0].y + cub->cell_size / 2) / cub->cell_size][(cub->player_image->instances[0].x + cub->cell_size / 2) / cub->cell_size] != '1' */)
			update_position(cub, next_x, next_y, Y_DIR);
	}
}

// get pixel size of mini_map img
//		cub->map_size.x * cub->cell_size, cub->map_size.y * cub->cell_size
// add player height and width as buffer
//		cub->cell_size / 2
// if position of player + his width or height = '1' on the map don't move
//		if (map[cub->pos_player.y * cub->cell_size + cub->cell_size / 2][cub->pos_player.x * cub->cell_size + cub->cell_size / 2] != '1')
// player position should be at center of the mini_map img
//
// thus the buffer should be half of the player_width/height converted

// cub->map[(cub->player_image->instances[0].y + cub->cell_size / 2) / cub->cell_size][(cub->player_image->instances[0].x + cub->cell_size / 2) / cub->cell_size] != '1'
// -> does not work

void	ft_key_hook(void* param)
{
	t_cub *cub = param;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		movement(cub, 0.07, 0);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		movement(cub, -0.07, 0);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		movement(cub, 0.07, 1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		movement(cub, -0.07, 1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		rotation(cub, -0.05);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		rotation(cub, 0.05);
}

// movement speed is faster when pressing two keys
