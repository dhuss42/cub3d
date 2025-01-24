/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:21 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/16 13:53:36 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_mini_map(t_game *game)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y; // The actual pixel location on the window (map location * cell_size)


	game->mini_map.pos_player_mm_x = game->pos_player.x - 0.5;
	game->mini_map.pos_player_mm_y = game->pos_player.y - 0.5;
	//render distance
	printf(RED"game->mini_map.pos_player_mm_x: %d\n"WHITE, game->mini_map.pos_player_mm_x);
	printf(RED"game->mini_map.pos_player_mm_y: %d\n"WHITE, game->mini_map.pos_player_mm_y);
	game->mini_map.min_x = game->mini_map.pos_player_mm_x - game->mini_map.render_distance;
	game->mini_map.max_x = game->mini_map.pos_player_mm_x + game->mini_map.render_distance;
	game->mini_map.min_y = game->mini_map.pos_player_mm_y - game->mini_map.render_distance;
	game->mini_map.max_y = game->mini_map.pos_player_mm_y + game->mini_map.render_distance;
	printf(YELLOW"game->m_map_size.x %d\n"WHITE, game->map_size.x);
	printf(YELLOW"game->m_map_size.y %d\n"WHITE, game->map_size.y);
	// calculate min and max for x and y 
	//	the players position on the map - or + the render distance
	if (game->mini_map.min_x < 0)
		game->mini_map.min_x = 0;
	if (game->mini_map.max_x > game->map_size.x - 1) // not 100% here
		game->mini_map.max_x = game->map_size.x - 1;
	if 	(game->mini_map.min_y < 0)
		game->mini_map.min_y = 0;
	if (game->mini_map.max_y > game->map_size.y - 1) // not 100% here
		game->mini_map.max_y = game->map_size.y - 1;
	// ensure the min and max values are within bounds
	//	if min_x < 0 it is 0
	// set y = min_y and loop until y <= y_max
	// same for x
	y = game->mini_map.min_y;
	printf("y: %d\n", y);
	while (y <= game->mini_map.max_y)
	{
		x = game->mini_map.min_x;
		printf("x: %d\n", x);
		while (x <= game->mini_map.max_x)
		{
			start_x = (x - game->mini_map.min_x) * game->cell_size;
			start_y = (y - game->mini_map.min_y) * game->cell_size;
			// determines where to start drawing
			if (game->map[y][x] == '1')
				draw_cell(game->map_image, start_x, start_y, game->cell_size - 1, 0x000000FF, game);
			else if (game->map[y][x] == '0')
				draw_cell(game->map_image, start_x, start_y, game->cell_size - 1, 0xFFFFFFFF, game);
			else if (is_player(game->map[y][x], game))
				draw_cell(game->map_image, start_x, start_y, game->cell_size - 1, 0xFFFFFFFF, game);
			else
				draw_cell(game->map_image, start_x, start_y, game->cell_size - 1, 0xCCCCCCFF, game);
			x++;
		}
		y++;
	}
	// interates over map and draws cells according to 1 and 0
	// displays image on window at x = 0 and y = 0
}

void	mini_map_size_bonus(t_game *game)
{
	game->m_map_size.x = game->width / 4;
	game->m_map_size.y = game->height / 4;
	// new_image(game->mlx, &game->map_image, game->map_size.x * game->cell_size, game->map_size.y * game->cell_size);
	new_image(game->mlx, &game->map_image, game->m_map_size.x, game->m_map_size.y);
}

void	mini_map_bonus(t_game *game)
{
	// printf("test0\n");
	game->cell_size = 32;
	game->mini_map.render_distance = 5;
	mini_map_size_bonus(game);
	draw_mini_map(game);
	draw_player(game);
	mlx_image_to_window(game->mlx, game->map_image, 10, 10); // change here to move into screen but also means changing player to be rendered new every time
	// printf("test2\n");
	// printf("test3\n");
	// printf("test4\n");
}

// render map based on player position
// make player icon rotate -> means it must be based on direction vector