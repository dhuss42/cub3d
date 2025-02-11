/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   drawing.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dhuss <dhuss@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/13 10:07:07 by dhuss			 #+#	#+#			 */
/*   Updated: 2025/02/10 10:49:15 by dhuss			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../cub.h"

// out of boudns check
void	draw_direction(t_game *game, float dir_x, float dir_y)
{
	int		pixel_x;
	int		pixel_y;
	int		draw_x;
	int		draw_y;
	float	step;

	step = 0;
	pixel_x = game->pos_player.x * game->cell_size;
	pixel_y = game->pos_player.y * game->cell_size;
	while (step < 10)
	{
		draw_x = pixel_x + dir_x * step;
		draw_y = pixel_y + dir_y * step;
		if (draw_x >= 0 && draw_y >= 0)
			mlx_put_pixel(game->map_image, draw_x, draw_y, 0x0C0FF0FF);
		step += 0.001;
	}
}

void	draw_player(t_game *game)
{
	int	player_pixel_x;
	int	player_pixel_y;

	player_pixel_y = game->pos_player.y * game->cell_size;
	player_pixel_x = game->pos_player.x * game->cell_size;
	draw_cell(game, player_pixel_x - game->cell_size / 4,
		player_pixel_y - game->cell_size / 4, 0xFFFF00FF);
	draw_direction(game, game->dir_player.x, game->dir_player.y);
}

void	draw_rotable_player(t_game *game, t_player_map *pm)
{
	float	dx;
	float	dy;
	float	local_x;
	float	local_y;
	int		grid_x;
	int		grid_y;

	grid_x = (int)(game->pos_player.x * game->cell_size - game->cell_size / 8); // starting position scaled
	grid_y = (int)(game->pos_player.y * game->cell_size - game->cell_size / 8);
	printf("grid_x: %d\n", grid_x);
	printf("grid_y: %d\n", grid_y);
	printf("pos_player.x: %f\n", game->pos_player.x);
	printf("pos_player.y: %f\n", game->pos_player.y);

	pm->x = pm->min_x;
	pm->y = pm->min_y;
	printf(GREEN"pm->x: %f\n"WHITE, pm->x);
	printf(RED"pm->max_x: %f\n"WHITE, pm->max_x);
	printf(GREEN"pm->y: %f\n"WHITE, pm->y);
	printf(RED"pm->max_y: %f\n"WHITE, pm->max_y);
	printf(YELLOW"distance min y %f\n"WHITE, fabs(pm->min_y - game->pos_player.y));
	printf(YELLOW"distance min x %f\n"WHITE, fabs(pm->min_x - game->pos_player.x));
	printf(YELLOW"distance max y %f\n"WHITE, fabs(pm->max_y - game->pos_player.y));
	printf(YELLOW"distance max x %f\n"WHITE, fabs(pm->max_x - game->pos_player.x));
	while (pm->x <= pm->max_x)
	{
		pm->y = pm->min_y;
		while (pm->y <= pm->max_y)
		{
			dx = pm->x - game->pos_player.x;
			dy = pm->y - game->pos_player.y;
			local_x = dx * game->dir_player.x + dy * game->dir_player.y;
			local_y = -dx * pm->perp_x - dy * pm->perp_y;
			if (fabs(local_x) <= pm->half_size && fabs(local_y) <= pm->half_size)
			{
				if (grid_x + pm->x >= 0 && grid_y + pm->y >= 0)
				{
					mlx_put_pixel(game->map_image, grid_x + pm->x, grid_y + pm->y, 0xFFFF00FF);
				}
				if (pm->x == pm->min_x || pm->x == pm->max_x) // DEBUGGING
					mlx_put_pixel(game->map_image, grid_x + pm->x, grid_y + pm->y, 0xFF0000FF);
				if (pm->y == pm->min_y || pm->y == pm->max_y) // DEBUGGING
					mlx_put_pixel(game->map_image, grid_x + pm->x, grid_y + pm->y, 0x000AF0FF);
			}
			pm->y++;
		}
		pm->x++;
	}
}

// finds the min and max x and y values of all the corners
// important because the x and y values are d
//		ifferent for the corners (because rotable)
// need these values to start and stop drawing
void	bounding_box(t_player_map *pm)
{
	float	corners[4][2];
	int		i;

	i = 0;
	while (i < 4)
	{
		corners[i][0] = pm->corners[i][0];
		corners[i][1] = pm->corners[i][1];
		i++;
	}
	pm->min_x = fmin(fmin(corners[0][0], corners[1][0]), fmin(corners[2][0], corners[3][0]));
	pm->max_x = fmax(fmax(corners[0][0], corners[1][0]), fmax(corners[2][0], corners[3][0]));
	pm->min_y = fmin(fmin(corners[0][1], corners[1][1]), fmin(corners[2][1], corners[3][1]));
	pm->max_y = fmax(fmax(corners[0][1], corners[1][1]), fmax(corners[2][1], corners[3][1]));
	printf("min_x: %f\n", pm->min_x);
	printf("max_x: %f\n", pm->max_x);
	printf("min_y: %f\n", pm->min_y);
	printf("max_y: %f\n", pm->max_y);
}

// determines the four corners of the square to be drawn
void	init_corners(t_game *game, t_player_map *pm)
{
	pm->corners[0][0] = game->pos_player.x + pm->half_size * game->dir_player.x + pm->half_size * pm->perp_x;
	pm->corners[0][1] = game->pos_player.y + pm->half_size * game->dir_player.y + pm->half_size * pm->perp_y;
	pm->corners[1][0] = game->pos_player.x - pm->half_size * game->dir_player.x + pm->half_size * pm->perp_x;
	pm->corners[1][1] = game->pos_player.y - pm->half_size * game->dir_player.y + pm->half_size * pm->perp_y;
	pm->corners[2][0] = game->pos_player.x - pm->half_size * game->dir_player.x - pm->half_size * pm->perp_x;
	pm->corners[2][1] = game->pos_player.y - pm->half_size * game->dir_player.y - pm->half_size * pm->perp_y;
	pm->corners[3][0] = game->pos_player.x + pm->half_size * game->dir_player.x - pm->half_size * pm->perp_x;
	pm->corners[3][1] = game->pos_player.y + pm->half_size * game->dir_player.y - pm->half_size * pm->perp_y;

	printf("bottom right x %f\n", pm->corners[0][0]);
	printf("bottom right y %f\n", pm->corners[0][1]);
	printf("top right x %f\n", pm->corners[1][0]);
	printf("top right y %f\n", pm->corners[1][1]);
	printf("top left x %f\n", pm->corners[2][0]);
	printf("top left y %f\n", pm->corners[2][1]);
	printf("bottom left x %f\n", pm->corners[3][0]);
	printf("bottom left y %f\n", pm->corners[3][1]);
	float center_x = (pm->corners[0][0] + pm->corners[2][0]) / 2;
	float center_y = (pm->corners[0][1] + pm->corners[2][1]) / 2;
	printf("Calculated center x: %f, y: %f\n", center_x, center_y);
	printf("Actual player x: %f, y: %f\n", game->pos_player.x, game->pos_player.y);
}

void	rotable_player(t_game *game)
{
	t_player_map	player_map;

	player_map.half_size = game->cell_size / 4.0;
	player_map.perp_x = -game->dir_player.y;
	player_map.perp_y = game->dir_player.x;
	init_corners(game, &player_map);
	bounding_box(&player_map);
	draw_rotable_player(game, &player_map);
	draw_direction(game, game->dir_player.x, game->dir_player.y);
}

/* Draws a square on the passed image starting from the passed x
and y starting position and according to the passed size and colour */
void	draw_cell(t_game *game, int start_x, int start_y, uint32_t color)
{
	int	y;
	int	x;
	int	cell;

	cell = game->cell_size - 1;
	if (start_x >= game->map_size.x * cell
		|| start_y >= game->map_size.y * cell)
		return ;
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
// starts from top (y = 0) left (x = 0)
//		going to the right edge of the cell
// always checks if still in bounds
//		by adding starting position to the position within the cell
// draws a pixel at the starting position + the position within
//		the cell thus getting the actual pixel on the screen
