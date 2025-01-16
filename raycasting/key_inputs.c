/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:08:40 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/14 13:20:07 by dhuss            ###   ########.fr       */
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

// checks if the next cell is a wall, if not then the player is moved according to the pressed key and passed speed
// moves the player on the minimap in corresponding pixel distance
//	-> buffer acts as a small buffer zone between player and wall
void	movement(t_cub *cub, float speed)
{
	float	next_x;
	float	next_y;
	float	buffer;

	buffer = 0.1;
	next_x = cub->pos_player.x + cub->dir_player.x * speed;
	next_y = cub->pos_player.y + cub->dir_player.y * speed;
	if (cub->map[(int)cub->pos_player.y][(int)(next_x + cub->dir_player.x * buffer)] != '1')
	{
		cub->pos_player.x = next_x;
		cub->player_image->instances[0].x = cub->pos_player.x * cub->cell_size;
	}
	if (cub->map[(int)(next_y + cub->dir_player.y * buffer)][(int)cub->pos_player.x] != '1')
	{
		cub->pos_player.y = next_y;
		cub->player_image->instances[0].y = cub->pos_player.y * cub->cell_size;
	}
	// printf(GREEN"x = %d\n"WHITE, cub->player_image->instances[0].x);
	// printf(GREEN"y = %d\n"WHITE, cub->player_image->instances[0].y);
	// printf(BLUE"pos_player.x: %f\n"WHITE, cub->pos_player.x);
	// printf(BLUE"pos_player.y: %f\n"WHITE, cub->pos_player.y);
}

// need to change movement to wasd
// need to add sideways movement ad
// on minimap the player can movebackwards inside the wall segfaults sometimes
void	ft_key_hook(void* param)
{
	t_cub *cub = param;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
	{
		movement(cub, 0.07);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
	{
		movement(cub, -0.07);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		rotation(cub, 0.05);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		rotation(cub, -0.05);
	}
}
