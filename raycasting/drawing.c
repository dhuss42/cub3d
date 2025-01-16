/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:07:07 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/16 14:35:10 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// function not up to date
void	draw_direction(t_cub *cub, float dir_x, float dir_y)
{
	int pixel_x; // The starting x-pixel position of the direction vector
	int pixel_y; // The starting y-pixel position of the direction vector
	int draw_x;
	int draw_y;
	float step = 0;
	float step_size = 0.001;
	float ray_length = 10.0;

	pixel_x = cub->pos_player.x * cub->cell_size + cub->cell_size / 4; // adjust to center

	pixel_y = cub->pos_player.y * cub->cell_size + cub->cell_size / 4;
	while (step < ray_length)
	{
		draw_x = pixel_x + dir_x * step;
		draw_y = pixel_y + dir_y * step;
		if (draw_x >= 0 && draw_x < cub->map_size.x * cub->cell_size && draw_y >= 0 && draw_y < cub->map_size.y * cub->cell_size)
			mlx_put_pixel(cub->map_image, draw_x, draw_y, 0x0C0FF0FF);
		step += step_size;
	}
}

void	draw_player(t_cub *cub)
{
	int player_pixel_x;
	int player_pixel_y;

	player_pixel_y = cub->pos_player.y * cub->cell_size + cub->cell_size / 2;
	player_pixel_x = cub->pos_player.x * cub->cell_size + cub->cell_size / 2;  // The starting pixel position of the player
	draw_cell(cub->player_image, 0, 0, cub->cell_size / 2, 0xFFFF00FF, cub);
	// y=0 and x=0 refer to the top left corner of the player image !! not the map

	draw_direction(cub, cub->dir_player.x, cub->dir_player.y);
	draw_direction(cub, cub->dir_player.x - cub->plane.x, cub->dir_player.y - cub->plane.y);
	draw_direction(cub, cub->dir_player.x + cub->plane.x, cub->dir_player.y + cub->plane.y);
	if (mlx_image_to_window(cub->mlx, cub->player_image, player_pixel_x, player_pixel_y) == -1)
		printf("Error mlx_image to window\n");
}


/* Draws a square on the passed image starting from the passed x and y starting position and according to the passed size and colour */
void	draw_cell(mlx_image_t *image, int start_x, int start_y, int cell_size, uint32_t color, t_cub *cub)
{
	int y;
	int x;

	if (start_x >= cub->map_size.x * cub->cell_size || start_y >= cub->map_size.y * cub->cell_size)
		return;
	y = 0;
	while (y < cell_size && (start_y + y) < cub->map_size.y * cub->cell_size)
	{
		x = 0;
		while (x < cell_size && (start_x + x) < cub->map_size.x * cub->cell_size)
		{
			mlx_put_pixel(image, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}
// checks if starting positions are on the screen
// starts from top (y = 0) left (x = 0) going to the right edge of the cell
// always checks if still in bounds by adding starting position to the position within the cell
// draws a pixel at the starting position + the position within the cell thus getting the actual pixel on the screen
