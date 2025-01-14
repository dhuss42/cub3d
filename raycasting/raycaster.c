/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:45 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/14 13:20:15 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	rays(t_cub *cub, int x)
{
	cub->camera_x = 2 * x / (float)(WIDTH / 2) -1;
	cub->ray_dir.x = cub->dir_player.x + cub->plane.x * cub->camera_x;
	cub->ray_dir.y = cub->dir_player.y + cub->plane.y * cub->camera_x;
	cub->map_pos.x = cub->pos_player.x;
	cub->map_pos.y = cub->pos_player.y;
	cub->dist_x = sqrt(1 + (cub->ray_dir.y * cub->ray_dir.y) / (cub->ray_dir.x * cub->ray_dir.x));
	// 1 is the distanced traveld in x direction
	// slope = y / x
	// y = x * slope
	// When x = 1, then y is the slope of raydir
	// --> ray_dir_y / ray_dir_x is the slope when x is exactly 1
	// --> y = 1 * raydirY / raydirX
	cub->dist_y = sqrt(1 + (cub->ray_dir.x * cub->ray_dir.x) / (cub->ray_dir.y * cub->ray_dir.y));
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
void	distance_to_first_side(t_cub *cub)
{
	cub->hit = 0;

	if (cub->ray_dir.x < 0)
	{
		cub->first_side_x = (cub->pos_player.x - cub->map_pos.x) * cub->dist_x;
		cub->step_x = -1;
	}
	else
	{
		cub->first_side_x = (cub->map_pos.x + 1 - cub->pos_player.x) * cub->dist_x;
		cub->step_x = 1;
	}
	if (cub->ray_dir.y < 0)
	{
		cub->first_side_y = (cub->pos_player.y - cub->map_pos.y) * cub->dist_y;
		cub->step_y = -1;
	}
	else
	{
		cub->first_side_y = (cub->map_pos.y + 1 - cub->pos_player.y) * cub->dist_y;
		cub->step_y = 1;
	}
}

// inital sideDistX and Y have to be calculated
//	 -if it has a negative x component first_side_x is the distance from the ray starting position
//	 to the first side to the left (map_pos.x)
//	 - if it has a positive x component it is the first side to right
//	 - same for y position but it is top and bottom
//	 Multiplied by dis_x/y because, in the case of ray_dir.x < 0, dis_x and first_side_x share the same slope
//	  --> first_side_x is a longer version of dis_x
//	  --> multiplying it by (cub->pos_player.x - cub->map_pos.x) means that when we go this far on the x-axis
//		  we go that far on the y-axis in relation to the shared slope
//	  --> probably because of the relation ship between dist_x and first_side_x
// also step_x and step_y
//	 if the ray has a negative x-component step_x is -1
//	 if positive +1
//	 same for Y

void draw_rays(t_cub *cub, int x)
{
	(void) x;
	// printf("x: %d\n", x);
	float ray_x = cub->pos_player.x;
	float ray_y = cub->pos_player.y;
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
		if (map_x < 0 || map_y < 0 || map_y >= 10 || map_x >= 10 || cub->map[map_y][map_x] == '1')
			break;

		// Convert world coordinates to screen pixel coordinates
		int pixel_x = (int)(ray_x * 64);  // 64 is the cell size in pixels
		int pixel_y = (int)(ray_y * 64);

		// Draw the ray as a cell at the player's current position
		// draw_cell(cub->image, pixel_x, pixel_y, 64, 0xFF0000FF); // Red color for ray
		mlx_put_pixel(cub->dir_image, pixel_x, pixel_y, 0xFF0000FF);

		// Move the ray forward
		ray_x += cub->ray_dir.x * step;
		ray_y += cub->ray_dir.y * step;
	}
}



/*
   Algorithm that iteratively advances the ray through the grid one cell at a time,
   adding the distance the ray travels to cross a cell boundary in the respective
   direction (x or y). Determines whether the ray hits a vertical or horizontal wall
   first and updates the position accordingly.
*/
void	dda(t_cub *cub) // Digital Differential Analysis
{
	// printf(YELLOW"hit %d\n", cub->hit);
	// printf("first_side_x %f\n", cub->first_side_x);
	// printf("first_side_y %f\n", cub->first_side_y);
	// printf("map_pos.x %d\n", cub->map_pos.x);
	// printf("map_pos.y %d\n", cub->map_pos.y);
	// printf("step_x %d\n", cub->step_x);
	// printf("step_y %d\n", cub->step_y);
	// printf("side %d\n"WHITE, cub->side);
	int run = 0;
	while (cub->hit == 0)
	{
		// printf(GREEN"run [%d]\n"WHITE, run);
		if (cub->first_side_x < cub->first_side_y)
		{
			// printf("x < y\n");
			cub->first_side_x += cub->dist_x;
			cub->map_pos.x += cub->step_x;
			cub->side = 0;
		}
		// if the distance to the next x-side is smaller than to the next y-side
		// the ray crosses a vertical line first (y-axis)
		// increment the first_side_x by dist_x
		//  the distance the ray travels when moving one cell in the x-direction
		else
		{
			// printf("y >= x\n");
			cub->first_side_y += cub->dist_y;
			cub->map_pos.y += cub->step_y;
			cub->side = 1;
		}
		// printf("cub->map_pos.y: %d\n", cub->map_pos.y);
		// printf("cub->map_pos.x: %d\n", cub->map_pos.x);
		// printf("char : %c\n", cub->map[cub->map_pos.y][cub->map_pos.x]);
		if (cub->map[cub->map_pos.y][cub->map_pos.x] == '1') //
		{
			// printf("hit = 1\n");
			cub->hit = 1;
		}
		run++;
	}
}


void	plane_to_wall_distance(t_cub *cub)
{
	if (cub->side == 0)
		cub->plane_wall_dist = (cub->first_side_x - cub->dist_x);
	else
		cub->plane_wall_dist = (cub->first_side_y - cub->dist_y);
}

// do not understand the maths involved here

void	calculate_line_height(t_cub *cub)
{
	// printf(YELLOW"plane_wall_dist: %f\n"WHITE, cub->plane_wall_dist);


	cub->line_height = (int)HEIGHT / cub->plane_wall_dist;
	cub->line_start = -cub->line_height / 2 + (int)HEIGHT / 2;
	if (cub->line_start < 0)
		cub->line_start = 0;
	cub->line_end = cub->line_height / 2 + (int)HEIGHT / 2;
	if (cub->line_start >= HEIGHT)
		cub->line_start = (int)HEIGHT - 1;

}

// - inverse (Kehrwert) of perpWallDist multiplied by h (height in pixels of the screen)
// -> 1 / perpWallDist
// -> this is done because things that are closer appear larger and vice versa (Umgekehrt proportional)

// don't understand the line_height / 2 part
// determines line to be drawn in the center of the screen HEIGHT / 2
// checks that the line is not drawn out of bounds (if checks)

void	draw_walls(t_cub *cub, int x)
{
	int y;

	// printf(YELLOW"line_start: %d\n", cub->line_start);
	// printf(YELLOW"line_end: %d\n"WHITE, cub->line_end);

	cub->colour = 0x0F00F0FF;
	if (cub->side == 1)
		cub->colour = cub->colour / 2;
	y = cub->line_start;
	while (y <= cub->line_end)
	{
		// printf("test7\n");
		if (y > 0 && y < HEIGHT && (x + WIDTH / 2) > WIDTH / 2 && (x + WIDTH / 2) < WIDTH)
			mlx_put_pixel(cub->map_image, (WIDTH / 2) + x, y, cub->colour);
		y++;
	}
}

void	raycaster(t_cub *cub)
{
	int x;

	x = 0;
	// printf(RED"pos_player-x: %f\n"WHITE, cub->pos_player.x);
	// printf(RED"pos_player-y: %f\n"WHITE, cub->pos_player.y);
	int run = 0;
		while (x < WIDTH / 2)
		{
			// printf(GREEN"run [%d]\n"WHITE, run);
			// printf("test1\n");
			rays(cub, x);
			// printf("test2\n");
			distance_to_first_side(cub);
			// printf("test3\n");
			dda(cub);
			// printf("test4\n");
			plane_to_wall_distance(cub);
			// printf("test5\n");
			calculate_line_height(cub);
			draw_walls(cub, x);
			// draw_rays(cub, x);
			// printf("test6\n");
			x++;
			run ++;
	}
	// mlx_image_to_window(cub->mlx, cub->drawn_walls, WIDTH / 2, 0);
}
