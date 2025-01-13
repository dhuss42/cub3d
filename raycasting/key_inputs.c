/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:08:40 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/13 14:48:55 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	rotation(t_cub *cub, float angle)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = cub->dir_player.x; // 0
	cub->dir_player.x = cub->dir_player.x * cos(angle) - cub->dir_player.y * sin(angle);
	cub->dir_player.y = old_dir_x * sin(angle) + cub->dir_player.y * cos(angle);

	old_plane_x = cub->plane.x;
	cub->plane.x = cub->plane.x * cos(angle) - cub->plane.y * sin(angle);
	cub->plane.y = old_plane_x * sin(angle) + cub->plane.y * cos(angle);
}

void	ft_key_hook(void* param)
{
	t_cub *cub = param;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP) && (cub->player_image->instances[0].y >= 1) && cub->map[(cub->player_image->instances[0].y - 5) / 64][cub->player_image->instances[0].x / 64] != '1')
	{
		cub->player_image->instances[0].y -= 5;
		cub->dir_image->instances[0].y -= 5;
		cub->pos_player.y -= 5.0 / 64.0;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN) && (cub->player_image->instances[0].y <= HEIGHT - 31) && cub->map[(cub->player_image->instances[0].y + 36) / 64][cub->player_image->instances[0].x / 64] != '1')
	{
		cub->player_image->instances[0].y += 5;
		cub->dir_image->instances[0].y += 5;
		cub->pos_player.y += 5.0 / 64.0;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) && (cub->player_image->instances[0].x >= 1) && cub->map[cub->player_image->instances[0].y / 64][(cub->player_image->instances[0].x - 5) / 64] != '1')
	{
		// cub->player_image->instances[0].x -= 5; // movement on minimap
		// cub->dir_image->instances[0].x -= 5;
		// cub->pos_player.x -= 5.0 / 64.0; // conversion to world movement
		rotation(cub, -0.1);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT) && (cub->player_image->instances[0].x <= (WIDTH / 2) - 31) && cub->map[(cub->player_image->instances[0].y) / 64][(cub->player_image->instances[0].x + 36) / 64] != '1')
	{
		// cub->player_image->instances[0].x += 5;
		// cub->dir_image->instances[0].x += 5;
		// cub->pos_player.x += 5.0 / 64.0;
		rotation(cub, 0.1);
	}
	// printf("x = %d\n", cub->player_image->instances[0].x);
	// printf("y = %d\n", cub->player_image->instances[0].y);
}

// values for the boarder have to be changed later, although the program should also always track the current cell and check if the cell is a 1
