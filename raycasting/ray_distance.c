/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:53:43 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/11 11:02:12 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	game->dist_x = sqrt(1 + (game->ray_dir.y * game->ray_dir.y)
			/ (game->ray_dir.x * game->ray_dir.x));
	game->dist_y = sqrt(1 + (game->ray_dir.x * game->ray_dir.x)
			/ (game->ray_dir.y * game->ray_dir.y));
}

/*
	Calculates the initial distances
		to the first grid line (side) intersected by the ray
	along the x and y axes. Determines the step direction for the ray
	(left/right or up/down) based on the ray's direction.
*/
void	distance_to_first_side(t_game *g)
{
	g->hit = 0;
	if (g->ray_dir.x < 0)
	{
		g->step_x = -1;
		g->first_side_x = (g->pos_player.x - g->map_pos.x) * g->dist_x;
	}
	else
	{
		g->step_x = 1;
		g->first_side_x = (g->map_pos.x + 1 - g->pos_player.x) * g->dist_x;
	}
	if (g->ray_dir.y < 0)
	{
		g->step_y = -1;
		g->first_side_y = (g->pos_player.y - g->map_pos.y) * g->dist_y;
	}
	else
	{
		g->step_y = 1;
		g->first_side_y = (g->map_pos.y + 1 - g->pos_player.y) * g->dist_y;
	}
}

//inital sideDistX and Y have to be calculated
//	-if it has a negative x component
//		first_side_x is the distance from the ray starting position
//	to the first side to the left (map_pos.x)
//	- if it has a positive x component it is the first side to right
//	- same for y position but it is top and bottom
//	Multiplied by dis_x/y because, in the case of ray_dir.x < 0,
//		dis_x and first_side_x share the same slope
//		--> first_side_x is a longer version of dis_x
//		--> multiplying it by (game->pos_player.x - game->map_pos.x)
//				means that when we go this far on the x-axis
//			we go that far on the y-axis in relation to the shared slope
//		--> probably because of the
//				relation ship between dist_x and first_side_x
//	also step_x and step_y
//		if the ray has a negative x-component step_x is -1
//	 	f positive +1
//		same for Y

/*
	Digital Differential Analysis
	iteratively advancest ray through the grid one cell at a time,
	adds distance ray travels to cross cell boundary in dir (x/y)
	Checks if ray hit a vertical or horizontal wall
	updates the position accordingly.
	if the distance to the next x-side < next y-side
		-> ray crosses a vertical line first (y-axis)
		-> increment first_side_x by dist_x
		(dist ray travels when moving one cell in the x-direction)
*/
void	dda(t_game *game)
{
	while (game->hit == 0)
	{
		if (game->first_side_x < game->first_side_y)
		{
			game->first_side_x += game->dist_x;
			game->map_pos.x += game->step_x;
			game->side = 0;
		}
		else
		{
			game->first_side_y += game->dist_y;
			game->map_pos.y += game->step_y;
			game->side = 1;
		}
		if (game->map[game->map_pos.y][game->map_pos.x] == '1')
		{
			game->hit = 1;
		}
	}
}

void	plane_to_wall_distance(t_game *game)
{
	if (game->side == 0)
	{
		game->plane_wall_dist = (game->map_pos.x - game->pos_player.x
				+ (1 - game->step_x) / 2) / game->ray_dir.x;
	}
	else
	{
		game->plane_wall_dist = (game->map_pos.y - game->pos_player.y
				+ (1 - game->step_y) / 2) / game->ray_dir.y;
	}
}

// do not understand the maths involved here

// - inverse (Kehrwert) of perpWallDist
//		 multiplied by h (height in pixels of the screen)
// -> 1 / perpWallDist
// -> this is done because things that are
//		closer appear larger and vice versa (Umgekehrt proportional)
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
