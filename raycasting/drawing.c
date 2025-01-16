/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:07:07 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/14 14:37:45 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_direction(t_cub *cub, float dir_x, float dir_y)
{
	int pixel_x; // The starting x-pixel position of the direction vector
	int pixel_y; // The starting y-pixel position of the direction vector
	float step = 0;
	float step_size = 0.1;
	float ray_length = 200.0;

	pixel_x = cub->pos_player.x * 64 + 32; // adjust to center
	pixel_y = cub->pos_player.y * 64 + 32;
	while (step < ray_length)
	{
		int draw_x = pixel_x + dir_x * step;
		int draw_y = pixel_y + dir_y * step;

		if (draw_x >= 0 && draw_x < (WIDTH / 2) && draw_y >= 0 && draw_y < HEIGHT)
		{
			mlx_put_pixel(cub->dir_image, draw_x, draw_y, 0xFF0AA0FF);
		}
		step += step_size;
	}
}

void	draw_player(t_cub *cub)
{
	int player_pixel_x = cub->pos_player.x * cub->cell_size + cub->cell_size / 4;  // The starting pixel position of the player
	int player_pixel_y = cub->pos_player.y * cub->cell_size + cub->cell_size / 4;

	// printf(GREEN"playerpixel_x: %d\n"WHITE, player_pixel_x);
	// printf(GREEN"playerpixel_y: %d\n"WHITE, player_pixel_y);
	draw_cell(cub->player_image, 0, 0, cub->cell_size / 2, 0xFFFF00FF);
	// y=0 and x=0 refer to the top left corner of the player image !! not the map
	if (!(cub->dir_image = mlx_new_image(cub->mlx, WIDTH / 2, HEIGHT)))
		printf("Error mlx_image\n");
	draw_direction(cub, cub->dir_player.x, cub->dir_player.y);
	draw_direction(cub, cub->dir_player.x - cub->plane.x, cub->dir_player.y - cub->plane.y);
	draw_direction(cub, cub->dir_player.x + cub->plane.x, cub->dir_player.y + cub->plane.y);
	// mlx_image_to_window(cub->mlx, cub->dir_image, 0, 0);
	if (mlx_image_to_window(cub->mlx, cub->player_image, player_pixel_x, player_pixel_y) == -1)
		printf("Error mlx_image to window\n");
	// this passes the entire image on to the game window at the coordinates of the player's starting position
}


/* Draws a square on the passed image starting from the passed x and y starting position and according to the passed size and colour */
void	draw_cell(mlx_image_t *image, int start_x, int start_y, int cell_size, uint32_t color)
{
	int y;
	int x;

	if (start_x >= WIDTH || start_y >= HEIGHT)
		return;
	y = 0;
	while (y < cell_size && (start_y + y) < HEIGHT)
	{
		x = 0;
		while (x < cell_size && (start_x + x) < WIDTH)
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
