/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:53:43 by dhuss             #+#    #+#             */
/*   Updated: 2025/03/13 13:55:46 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*--------------------------------------------------------------*/
/* Calculates Ray Direction										*/
/* -> game->dir_player: central ray straight infront of player	*/
/* -> camera_x * game->plane: shifts ray left (-1) or right (+1)*/
/* -> adding the two vectors gice the direction of the ray		*/
/* 																*/
/* Determines Grid Position										*/
/* -> map_pos.x/y the current square we are in 					*/
/* 																*/
/* Calculates ray distance when moving one step in x or y		*/
/* -> dist_x: 1 is the distanced traveld in x direction			*/
/* -> raydirY / raydirX is the amount of units the ray travels	*/
/* 		in y when moving 1 in x									*/
/*--------------------------------------------------------------*/
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

/*--------------------------------------------------------------*/
/* Calculates the initial dist to the first grid line			*/
/* Determines the step direction for the ray					*/
/* -> (left/right or up/down) based on the ray's direction		*/
/*--------------------------------------------------------------*/
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

/*----------------------------------------------------------------------*/
/* Digital Differential Analysis										*/
/* iteratively advances ray through the grid one cell at a time 		*/
/* -> adds distance ray travels to cross cell boundary in dir (x/y)		*/
/* -> updates the position accordingly 									*/
/* 																		*/
/* checks if the next horizontal or vertical gridline is closer			*/
/* -> first_side_x: dist from player to next vertical line				*/
/* -> first_side_y: dist from player to next horizontal line			*/
/* if (first_side_x < first_side_y) 									*/
/* -> crosses vertical line before horizontal line						*/
/* -> increment first_side_x by dist_x 									*/
/*----------------------------------------------------------------------*/
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

/*--------------------------------------------------------------*/
/* Calculates the distance ray has travel from player to wall	*/
/*--------------------------------------------------------------*/
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

/*--------------------------------------------------------------*/
/* Calculate height of line to draw on screen					*/
// - inverse (Kehrwert) of game->plane_wall_dist				//
//		 multiplied by h (height in pixels of the screen)		//
// -> 1 / perpWallDist											//
// -> this is done because things that are						//
//		closer appear larger and vice versa 					//
/* Calculate heighest and lowest pixel of line					*/
/* -> from center of the screen height							*/
/*--------------------------------------------------------------*/
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
