/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:45 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/17 15:07:22 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	rays(t_game *game, int x)
{
	game->camera_x = 2 * x / (float)(game->width) -1;
	game->ray_dir.x = game->dir_player.x + game->plane.x * game->camera_x;
	game->ray_dir.y = game->dir_player.y + game->plane.y * game->camera_x;
	game->map_pos.x = (int)game->pos_player.x;
	game->map_pos.y = (int)game->pos_player.y;
	game->dist_x = sqrt(1 + (game->ray_dir.y * game->ray_dir.y) / (game->ray_dir.x * game->ray_dir.x));
	// 1 is the distanced traveld in x direction
	// slope = y / x
	// y = x * slope
	// When x = 1, then y is the slope of raydir
	// --> ray_dir_y / ray_dir_x is the slope when x is exactly 1
	// --> y = 1 * raydirY / raydirX
	game->dist_y = sqrt(1 + (game->ray_dir.x * game->ray_dir.x) / (game->ray_dir.y * game->ray_dir.y));

	// game->dist_x = fabs(1 / game->ray_dir.x);
	// game->dist_y = fabs(1 / game->ray_dir.y);
}

// camera_x: point on which the current ray will cross the camera plane
// ray_dir.x/y direction vector of the current ray
// map_pos.x/y the current square we are in
// dist_x/y is the distance the ray travels in the x/y direction when moving exactly one square on the opposite axis


/*
   Calculates the initial distances to the first grid line (side) intersected by the ray
   along the x and y axes. Determines the step direction for the ray
   (left/right or up/down) based on the ray's direction.
*/
void	distance_to_first_side(t_game *game)
{
	game->hit = 0;
	if (game->ray_dir.x < 0)
	{
		game->step_x = -1;
		game->first_side_x = (game->pos_player.x - game->map_pos.x) * game->dist_x;
	}
	else
	{
		game->step_x = 1;
		game->first_side_x = (game->map_pos.x + 1 - game->pos_player.x) * game->dist_x;
	}
	if (game->ray_dir.y < 0)
	{
		game->step_y = -1;
		game->first_side_y = (game->pos_player.y - game->map_pos.y) * game->dist_y;
	}
	else
	{
		game->step_y = 1;
		game->first_side_y = (game->map_pos.y + 1 - game->pos_player.y) * game->dist_y;
	}
}

// inital sideDistX and Y have to be calculated
//	 -if it has a negative x component first_side_x is the distance from the ray starting position
//	 to the first side to the left (map_pos.x)
//	 - if it has a positive x component it is the first side to right
//	 - same for y position but it is top and bottom
//	 Multiplied by dis_x/y because, in the case of ray_dir.x < 0, dis_x and first_side_x share the same slope
//	  --> first_side_x is a longer version of dis_x
//	  --> multiplying it by (game->pos_player.x - game->map_pos.x) means that when we go this far on the x-axis
//		  we go that far on the y-axis in relation to the shared slope
//	  --> probably because of the relation ship between dist_x and first_side_x
// also step_x and step_y
//	 if the ray has a negative x-component step_x is -1
//	 if positive +1
//	 same for Y

void draw_rays(t_game *game, int x)
{
	(void) x;
	// printf("x: %d\n", x);
	float ray_x = game->pos_player.x;
	float ray_y = game->pos_player.y;
	float step = 0.1; // Small increment for smooth ray drawing

	// Iterate over the ray's path
	while (1)
	{
		// printf("ray_x: %f\n", ray_x);
		// printf("ray_y: %f\n", ray_y);

		int map_x = (int)ray_x;
		int map_y = (int)ray_y;
		// printf("map_x: %d\n", map_x);
		// printf("map_y: %d\n", map_y);

		// Stop drawing if we hit a wall or go out of bounds
		if (map_x < 0 || map_y < 0 || map_y >= 10 || map_x >= 10 || game->map[map_y][map_x] == '1')
			break;

		// Convert world coordinates to screen pixel coordinates
		int pixel_x = (int)(ray_x * 64);  // 64 is the cell size in pixels
		int pixel_y = (int)(ray_y * 64);

		// Draw the ray as a cell at the player's current position
		// draw_cell(game->image, pixel_x, pixel_y, 64, 0xFF0000FF); // Red color for ray
		mlx_put_pixel(game->dir_image, pixel_x, pixel_y, 0xFF0000FF);

		// Move the ray forward
		ray_x += game->ray_dir.x * step;
		ray_y += game->ray_dir.y * step;
	}
}



/*
   Algorithm that iteratively advances the ray through the grid one cell at a time,
   adding the distance the ray travels to cross a cell boundary in the respective
   direction (x or y). Determines whether the ray hits a vertical or horizontal wall
   first and updates the position accordingly.
*/
void	dda(t_game *game) // Digital Differential Analysis
{
	// printf(YELLOW"hit %d\n", game->hit);
	// printf("first_side_x %f\n", game->first_side_x);
	// printf("first_side_y %f\n", game->first_side_y);
	// printf("map_pos.x %d\n", game->map_pos.x);
	// printf("map_pos.y %d\n", game->map_pos.y);
	// printf("step_x %d\n", game->step_x);
	// printf("step_y %d\n", game->step_y);
	// printf("side %d\n"WHITE, game->side);
	int run = 0;
	while (game->hit == 0)
	{
		// printf(GREEN"run [%d]\n"WHITE, run);
		if (game->first_side_x < game->first_side_y)
		{
			// printf("x < y\n");
			game->first_side_x += game->dist_x;
			game->map_pos.x += game->step_x;
			game->side = 0;
		}
		// if the distance to the next x-side is smaller than to the next y-side
		// the ray crosses a vertical line first (y-axis)
		// increment the first_side_x by dist_x
		//  the distance the ray travels when moving one cell in the x-direction
		else
		{
			// printf("y >= x\n");
			game->first_side_y += game->dist_y;
			game->map_pos.y += game->step_y;
			game->side = 1;
		}
		// printf("game->map_pos.y: %d\n", game->map_pos.y);
		// printf("game->map_pos.x: %d\n", game->map_pos.x);
		// printf("char : %c\n", game->map[game->map_pos.y][game->map_pos.x]);
		if (game->map[game->map_pos.y][game->map_pos.x] == '1') //
		{
			// printf("hit = 1\n");
			game->hit = 1;
		}
		run++;
	}
}


void	plane_to_wall_distance(t_game *game)
{
	if (game->side == 0)
		game->plane_wall_dist = (game->map_pos.x - game->pos_player.x + (1 -game->step_x) / 2) / game->ray_dir.x;
	else
		game->plane_wall_dist = (game->map_pos.y - game->pos_player.y + (1 -game->step_y) / 2) / game->ray_dir.y;
}

// do not understand the maths involved here

void	calculate_line_height(t_game *game)
{
	// printf(YELLOW"plane_wall_dist: %f\n"WHITE, game->plane_wall_dist);


	game->line_height = game->height / game->plane_wall_dist;
	game->line_start = -game->line_height / 2 + game->height / 2;
	if (game->line_start < 0)
		game->line_start = 0;
	game->line_end = game->line_height / 2 + game->height / 2;
	if (game->line_start >= game->height)
		game->line_start = game->height - 1;

}

// - inverse (Kehrwert) of perpWallDist multiplied by h (height in pixels of the screen)
// -> 1 / perpWallDist
// -> this is done because things that are closer appear larger and vice versa (Umgekehrt proportional)

// don't understand the line_height / 2 part
// determines line to be drawn in the center of the screen HEIGHT / 2
// checks that the line is not drawn out of bounds (if checks)

void	draw_walls(t_game *game, int x)
{
	int y;

	
	game->colour = 0x0F00F0FF;
	if (game->side == 1)
		game->colour = game->colour / 2;
	y = game->line_start;
	while (y <= game->line_end)
	{
		if (y > 0 && y < game->height && x > 0 && x < game->width)
			mlx_put_pixel(game->wall_image, x, y, game->colour);
		y++;
	}
}

// texture_y = (int)texture_pos & TEX_HEIGHT;
// -> handles overflow (valid range is 0 to TEX_HEIGHT)
// -> wraps round
void	loop_y_axis(t_game *game)
{
	float step;
	float texture_pos;
	int		y;
	int		texture_y;

	step = 1.0 * TEX_HEIGHT / game->line_height;
	texture_pos = (game->line_start - 100 - game->height / 2 + game->line_height / 2) * step;
	y = game->line_start;
	texture_y = (int)texture_pos % TEX_HEIGHT;
	printf("texture_pos: %f\n", texture_pos);
	printf("texture_y: %d\n", texture_y);
	while (y < game->line_end)
	{
		// texture_y = (int)texture_pos & (TEX_HEIGHT -1);
		texture_y = (int)texture_pos % TEX_HEIGHT;
		texture_pos += step;

		// ---- not understood yet --//
		size_t pixel_index = (TEX_WIDTH * texture_y + game->texture_x) * game->texture->bytes_per_pixel;

        // Extract RGBA color (assuming 4 bytes per pixel)
        uint8_t r = game->texture->pixels[pixel_index];
        uint8_t g = game->texture->pixels[pixel_index + 1];
        uint8_t b = game->texture->pixels[pixel_index + 2];
        // uint8_t a = game->texture->pixels[pixel_index + 3]; // Not used here, but available

        // Combine RGBA into a single Uint32 value
        u_int32_t color = (r << 16) | (g << 8) | b;
		(void) color;
		// buffer
		y++;
	}
}

// scales wall_x with texture width to get exact x-location on texture
// checks which side was hit (vertical/horizontal)
// also checks if right side or bottom was hit
// reverses image if both conditions true
// example texture_x = 50, subtracting it from entire width equals same distance from the end of the image
// -1 accounts for starting at 0
void	scale_to_texture_width(t_game *game)
{
	game->texture_x = game->wall_x * TEX_WIDTH;
	if (game->side == 0 && game->ray_dir.x > 0)
		game->texture_x = TEX_WIDTH - game->texture_x -1;
	if (game->side == 1 && game->ray_dir.y < 0)
		game->texture_x = TEX_WIDTH - game->texture_x -1;
	// printf(GREEN"location on texture: %d\n"WHITE, game->texture_x);
}

// determines the correct texture depending on the location on the map
// subtracts -1 because texture array start at 0 and Wall is 1 on map
// calculates where the ray hit the wall relative to the map grid
// checks if vertical wall or horizontal
// removes the integral part from the fractional part
// now wall_x is the percentage of the hitpoint on the x-axis of the texture
void	exact_hit_point(t_game *game)
{
	char str[2];

	str[0] = game->map[game->map_pos.y][game->map_pos.x] - 1;
	str[1] = '\0';
	game->tex_num = atoi(str); // change to ft_atoi
	if (game->side == 0)
		game->wall_x = game->pos_player.y + game->plane_wall_dist * game->ray_dir.y;
	else
		game->wall_x = game->pos_player.x + game->plane_wall_dist * game->ray_dir.x;
	// printf(YELLOW"wall_x before removing int: %f\n"WHITE, game->wall_x);
	game->wall_x -= floor(game->wall_x);
	// printf(YELLOW"wall_x after removing int: %f\n"WHITE, game->wall_x);
}

void	raycaster(t_game *game)
{
	int x;

	x = 0;
	while (x < game->width)
	{
		// printf("test1\n");
		rays(game, x);
		// printf("test2\n");
		distance_to_first_side(game);
		// printf("test3\n");
		dda(game);
		// printf("test4\n");
		plane_to_wall_distance(game);
		// printf("test5\n");
		calculate_line_height(game);
		// exact_hit_point(game);
		// scale_to_texture_width(game);
		// loop_y_axis(game);
		draw_walls(game, x);
		// draw_rays(game, x);
		// printf("test6\n");
		x++;
		// printf("x: %d\n", x);
	}
}
