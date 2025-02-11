/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:08:40 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/11 08:58:25 by dhuss            ###   ########.fr       */
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
// ADD in bounds check
void	movement(t_game *game, float speed, int sideways)
{
	float	next_x;
	float	next_y;
	float	move_x;
	float	move_y;

	is_side_dir(game, sideways, &move_x, &move_y);
	two_keys_pressed(game, &speed);
	next_x = game->pos_player.x + move_x * speed;
	next_y = game->pos_player.y + move_y * speed;
	if (!is_coliding(game, next_x, game->pos_player.y))
		update_position(game, next_x, game->pos_player.y, X_DIR);
	if (!is_coliding(game, game->pos_player.x, next_y))
		update_position(game, game->pos_player.x, next_y, Y_DIR);
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
