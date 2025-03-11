/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:56:02 by dhuss             #+#    #+#             */
/*   Updated: 2025/03/11 09:41:53 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// sets move_x/y to perpundicular to player direction vector
void	side_dir(t_game *game, int sideways, float *move_x, float *move_y)
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

// handles player like a box which detects
//		in a plaer radius if there are any walls
int	is_coliding(t_game *game, float x, float y)
{
	float	pr;

	pr = 0.2;
	return (game->map[(int)(y + pr)][(int)(x + pr)] == '1' ||
		game->map[(int)(y + pr)][(int)(x - pr)] == '1' ||
		game->map[(int)(y - pr)][(int)(x + pr)] == '1' ||
		game->map[(int)(y - pr)][(int)(x - pr)] == '1');
}

// halfs speed when moving diagonally
void	two_keys_pressed(t_game *game, float *speed)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)
		|| mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_D)
			|| mlx_is_key_down(game->mlx, MLX_KEY_A))
			*speed /= 2;
	}
}
