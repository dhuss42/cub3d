/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:45 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/07 13:47:12 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// camera_x: point on which the current ray will cross the camera plane
// ray_dir.x/y direction vector of the current ray
// map_pos.x/y the current square we are in
// dist_x/y is the distance the ray travels in the x/y direction when moving
//		exactly one square on the opposite axis
//	// 1 is the distanced traveld in x direction
	// slope = y / x
	// y = x * slope
	// When x = 1, then y is the slope of raydir
	// --> ray_dir_y / ray_dir_x is the slope when x is exactly 1
	// --> y = 1 * raydirY / raydirX
void	rays(t_game *game, int x)
{
	game->camera_x = 2 * x / (float)(game->width) - 1;
	game->ray_dir.x = game->dir_player.x + game->plane.x * game->camera_x;
	game->ray_dir.y = game->dir_player.y + game->plane.y * game->camera_x;
	game->map_pos.x = (int)game->pos_player.x;
	game->map_pos.y = (int)game->pos_player.y;
	game->dist_x = sqrt(1 + (game->ray_dir.y * game->ray_dir.y) / (game->ray_dir.x * game->ray_dir.x));
	game->dist_y = sqrt(1 + (game->ray_dir.x * game->ray_dir.x) / (game->ray_dir.y * game->ray_dir.y));
}

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


/*
   Algorithm that iteratively advances the ray through the grid one cell at a time,
   adding the distance the ray travels to cross a cell boundary in the respective
   direction (x or y). Determines whether the ray hits a vertical or horizontal wall
   first and updates the position accordingly.
*/
void	dda(t_game *game) // Digital Differential Analysis
{
	int run = 0;
	while (game->hit == 0)
	{
		if (game->first_side_x < game->first_side_y)
		{
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
			game->first_side_y += game->dist_y;
			game->map_pos.y += game->step_y;
			game->side = 1;
		}
		if (game->map[game->map_pos.y][game->map_pos.x] == '1') //
		{
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

// - inverse (Kehrwert) of perpWallDist multiplied by h (height in pixels of the screen)
// -> 1 / perpWallDist
// -> this is done because things that are closer appear larger and vice versa (Umgekehrt proportional)
// don't understand the line_height / 2 part
// determines line to be drawn in the center of the screen HEIGHT / 2
// checks that the line is not drawn out of bounds (if checks)
void	calculate_line_height(t_game *game)
{
	game->line_height = game->height / game->plane_wall_dist;
	game->line_start = -game->line_height / 2 + game->height / 2;
	if (game->line_start < 0)
		game->line_start = 0;
	game->line_end = game->line_height / 2 + game->height / 2;
	if (game->line_start >= game->height)
		game->line_start = game->height - 1;

}


int rgba_colours(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// function loops through the vertical line of each point on the x axis
// step: the increment in texture coordinates
// texture_pos is the starting texture coordinate for the current vertical line
//	line_start is the starting y-coordinate of the wall segment on the screen
//	height / 2 Centers the screen vertically
//	line_height centers the wall texture vertically relative to its segment
// y is the vertical screen pixel currently being processed
// texture_y is the corresponding texture y-coordinate
// texture_y = (int)texture_pos & game->texture[game->tex_num]->height;
// -> handles overflow (valid range is 0 to game->texture[game->tex_num]->height)
// -> wraps round
void	loop_y_axis(t_game *game, int x)
{
	float			step;
	float			texture_pos;
	int				y;
	int				texture_y;
	unsigned int	i;
	mlx_texture_t	texture;

	step = 1.0 * game->texture[game->tex_num]->height / game->line_height;
	texture_pos = (game->line_start - game->height / 2 + game->line_height / 2) * step;
	y = game->line_start;
	texture_y = (int)texture_pos % game->texture[game->tex_num]->height;
	texture = *game->texture[game->tex_num];
	while (y < game->line_end)
	{
		texture_y = (int)texture_pos % texture.height;
		if (texture_y < 0)
			texture_y += texture.height;
		texture_pos += step;
		i = (texture_y * texture.width + game->texture_x) * 4;
		game->colour = (rgba_colours(texture.pixels[i], texture.pixels[i + 1], texture.pixels[i + 2], texture.pixels[i + 3]));
		if (y > 0 && y < game->height && x > 0 && x < game->width)
			mlx_put_pixel(game->wall_image, x, y, game->colour);
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
	game->texture_x = game->wall_x * game->texture[game->tex_num]->width;
	if (game->side == 0 && game->ray_dir.x > 0)
		game->texture_x = game->texture[game->tex_num]->width - game->texture_x -1;
	if (game->side == 1 && game->ray_dir.y < 0)
		game->texture_x = game->texture[game->tex_num]->width - game->texture_x -1;
}

// determines the correct texture depending on the location on the map
// subtracts -1 because texture array start at 0 and Wall is 1 on map
// calculates where the ray hit the wall relative to the map grid
// checks if vertical wall or horizontal
// removes the integral part from the fractional part
// now wall_x is the percentage of the hitpoint on the x-axis of the texture
void	exact_hit_point(t_game *game)
{
	if (game->side == 0)
	{
		game->wall_x = game->pos_player.y + game->plane_wall_dist * game->ray_dir.y;
		if (game->ray_dir.x > 0)
			game->tex_num = 2;
		else
			game->tex_num = 3;
	}
	else
	{
		game->wall_x = game->pos_player.x + game->plane_wall_dist * game->ray_dir.x;
		if (game->ray_dir.y < 0)
			game->tex_num = 0;
		else
			game->tex_num = 1;
	}
	game->wall_x -= floor(game->wall_x);
}

void	raycaster(t_game *game)
{
	int x;

	x = 0;
	while (x < game->width)
	{
		rays(game, x);
		distance_to_first_side(game);
		dda(game);
		plane_to_wall_distance(game);
		calculate_line_height(game);
		exact_hit_point(game);
		scale_to_texture_width(game);
		loop_y_axis(game, x);
		x++;
	}
}
