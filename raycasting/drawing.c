/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:07:07 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/17 12:24:37 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// function not up to date
void	draw_direction(t_game *game, float dir_x, float dir_y)
{
	int pixel_x; // The starting x-pixel position of the direction vector
	int pixel_y; // The starting y-pixel position of the direction vector
	int draw_x;
	int draw_y;
	float step = 0;
	float step_size = 0.001;
	float ray_length = 10.0;

	pixel_x = game->pos_player.x * game->cell_size + game->cell_size / 4; // adjust to center
	pixel_y = game->pos_player.y * game->cell_size + game->cell_size / 4;
	while (step < ray_length)
	{
		draw_x = pixel_x + dir_x * step;
		draw_y = pixel_y + dir_y * step;
		if (draw_x >= 0 && draw_x < game->map_size.x * game->cell_size && draw_y >= 0 && draw_y < game->map_size.y * game->cell_size)
			mlx_put_pixel(game->map_image, draw_x, draw_y, 0x0C0FF0FF);
		step += step_size;
	}
}

void	draw_player(t_game *game)
{
	int player_pixel_x;
	int player_pixel_y;

	player_pixel_y = game->pos_player.y * game->cell_size;
	player_pixel_x = game->pos_player.x * game->cell_size;  // The starting pixel position of the player
	draw_cell(game, player_pixel_x - game->cell_size / 4, player_pixel_y - game->cell_size / 4, 0xFFFF00FF);
	// y=0 and x=0 refer to the top left corner of the player image !! not the map
	draw_direction(game, game->dir_player.x, game->dir_player.y);
}


/* Draws a square on the passed image starting from the passed x and y starting position and according to the passed size and colour */
void	draw_cell(t_game *game, int start_x, int start_y, uint32_t color)
{
	int y;
	int x;
    int cell;

	// if (color == 0xFFFF00FF)
    // 	cell = game->cell_size  / 2;
	// else
		cell = game->cell_size - 1;
	if (start_x >= game->map_size.x * cell || start_y >= game->map_size.y * cell)
		return;
	y = 0;
	while (y < cell && (start_y + y) < game->map_size.y * cell)
	{
		x = 0;
		while (x < cell && (start_x + x) < game->map_size.x * cell)
		{
			mlx_put_pixel(game->map_image, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}
// checks if starting positions are on the screen
// starts from top (y = 0) left (x = 0) going to the right edge of the cell
// always checks if still in bounds by adding starting position to the position within the cell
// draws a pixel at the starting position + the position within the cell thus getting the actual pixel on the screen
