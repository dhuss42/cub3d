/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:08:40 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/07 14:05:14 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// saves the previous direction.x so it can
//		be used after the direction of x is updated
// the direction vector is updated with the formula
//	x' = x * cos(angle) - y * sin(angle)
//	y' = x * sin(angle) + y * cos(angle)
// then the camera plane is updated according to the same
//		principle keeping it perpendicular to the direction vector
void	rotation(t_game *game, float angle)
{
	float		old_dir_x;
	float		old_plane_x;
	t_vector	dir;

	old_dir_x = game->dir_player.x;
	dir.x = game->dir_player.x * cos(angle) - game->dir_player.y * sin(angle);
	dir.y = old_dir_x * sin(angle) + game->dir_player.y * cos(angle);
	old_plane_x = game->plane.x;
	game->plane.x = game->plane.x * cos(angle) - game->plane.y * sin(angle);
	game->plane.y = old_plane_x * sin(angle) + game->plane.y * cos(angle);
	game->dir_player = dir;
}

// determines in which direction the buffer
//		should be added based on the passed speed
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
void	is_side_dir(t_game *game, int sideways, float *move_x, float *move_y)
{
	if (sideways)
	{
		*move_x = game->dir_player.y;
		*move_y = -game->dir_player.x;
	}
	else
	{
		*move_x = game->dir_player.x;
		*move_y = game->dir_player.y;
	}
}

// checks if next move in x/y direction is valid, prevents segfault
// should be changed to actual size, this size is not entirely correct
int	is_within_bounds(t_game *game, float x, float y)
{
	return (x >= 0 && x < game->map_size.x && y >= 0 && y < game->map_size.y);
}

// updates the player position according to the passed direction
// Also updates the player position on the minimap
void	update_position(t_game *game, float next_x, float next_y, int dir)
{
	if (dir == DIAGONAL)
	{
		game->pos_player.x = next_x;
		game->pos_player.y = next_y;
	}
	else if (dir == X_DIR)
	{
		game->pos_player.x = next_x;
	}
	else if (dir == Y_DIR)
	{
		game->pos_player.y = next_y;
	}
}

// checks if the next cell is a wall, if not then the player is
//		moved according to the pressed key and passed speed
// moves the player on the minimap in corresponding pixel distance
//	-> buffer acts as a small buffer zone between player and wall
void	movement(t_game *game, float speed, int sideways)
{
	float	next_x;
	float	next_y;
	float	move_x;
	float	move_y;
	float	check_buffer;

	check_buffer = 0;
	get_buffer_dir(speed, &check_buffer);
	is_side_dir(game, sideways, &move_x, &move_y);
	next_x = game->pos_player.x + move_x * speed;
	next_y = game->pos_player.y + move_y * speed;
	if (!is_within_bounds(game, next_x, game->pos_player.y) || !is_within_bounds(game, game->pos_player.x, next_y))
		return ;
	if (game->map[(int)(next_y + move_y * check_buffer)][(int)(next_x + move_x * check_buffer)] != '1') // do the same check for ' '
		update_position(game, next_x, next_y, DIAGONAL);
	else
	{
		if (game->map[(int)game->pos_player.y][(int)(next_x + move_x * check_buffer)] != '1') // do the same check for ' '
			update_position(game, next_x, next_y, X_DIR);
		if (game->map[(int)(next_y + move_y * check_buffer)][(int)game->pos_player.x] != '1') // do the same check for ' '
			update_position(game, next_x, next_y, Y_DIR);
	}
}

void	ft_key_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		movement(game, 0.07, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		movement(game, -0.07, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		movement(game, 0.07, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		movement(game, -0.07, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotation(game, -0.05);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotation(game, 0.05);
}

// movement speed is faster when pressing two keys
