/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:08:40 by dhuss             #+#    #+#             */
/*   Updated: 2025/03/11 14:38:30 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//------------------------------------------------------------------//
// the direction vector is updated with the formula					//
//	x' = x * cos(angle) - y * sin(angle)							//
//	y' = x * sin(angle) + y * cos(angle)							//
// then the camera plane is updated according to the same			//
//		principle keeping it perpendicular to the direction vector	//
//------------------------------------------------------------------//
void	rotation(t_game *game, float angle)
{
	// float		old_dir_x;
	float		old_plane_x;
	t_vector	dir;

	// old_dir_x = game->dir_player.x;
	dir.x = game->dir_player.x * cos(angle) - game->dir_player.y * sin(angle);
	dir.y = game->dir_player.x * sin(angle) + game->dir_player.y * cos(angle);
	game->dir_player = dir;
	old_plane_x = game->plane.x;
	game->plane.x = game->plane.x * cos(angle) - game->plane.y * sin(angle);
	game->plane.y = old_plane_x * sin(angle) + game->plane.y * cos(angle);
}

/*----------------------------------------------*/
/* updates the player position according		*/
/* 		to the passed direction					*/
/*----------------------------------------------*/
void	update_position(t_game *game, float next_x, float next_y, int dir)
{
	if (dir == X_DIR)
	{
		game->pos_player.x = next_x;
	}
	else if (dir == Y_DIR)
	{
		game->pos_player.y = next_y;
	}
}

/*----------------------------------------------*/
/* check if side (A/D)							*/
/* check if two keys pressed					*/
/* calculat where player would be next			*/
/* check if that pos + buffer is wall 			*/
/* if not the position is updated				*/
/*----------------------------------------------*/
void	movement(t_game *game, float speed, int sideways)
{
	float	next_x;
	float	next_y;
	float	move_x;
	float	move_y;

	side_dir(game, sideways, &move_x, &move_y);
	two_keys_pressed(game, &speed);
	next_x = game->pos_player.x + move_x * speed;
	next_y = game->pos_player.y + move_y * speed;
	if (!is_coliding(game, next_x, game->pos_player.y))
		update_position(game, next_x, game->pos_player.y, X_DIR);
	if (!is_coliding(game, game->pos_player.x, next_y))
		update_position(game, game->pos_player.x, next_y, Y_DIR);
}


/*----------------------------------------------*/
/* register key inputs							*/
/*----------------------------------------------*/
void	ft_key_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		free_mlx(game, 0, 2);
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
