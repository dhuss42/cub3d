/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:21 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/11 11:57:55 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
				draw_cell(game, start_x, start_y, 0x000000FF);
			else if (game->map[y][x] == '0')
				draw_cell(game, start_x, start_y, 0xFFFFFFFF);
			else if (is_player(game->map[y][x], game))
				draw_cell(game, start_x, start_y, 0xFFFFFFFF);
			else
				draw_cell(game, start_x, start_y, 0xCCCCCCFF);
			x++;
		}
		y++;
	}
}

void	mini_map_size_bonus(t_game *game)
{
	game->m_map_size.x = game->width / 4;
	game->m_map_size.y = game->height / 4;
	game->map_image = mlx_new_image(game->mlx, game->m_map_size.x,
			game->m_map_size.y);
	if (!game->mlx)
		print_error_free_exit(E_MLXIMG, game->cub, "map_image");
}

void	mini_map_bonus(t_game *game)
{
	game->cell_size = 32;
	game->mini_map.render_distance = 5;
	mini_map_size_bonus(game);
	// draw_mini_map(game);
	draw_player(game);
	if (mlx_image_to_window(game->mlx, game->map_image, 10, 10) == -1)
		print_error_free_exit(E_MLXIMGTOWIN, game->cub, NULL);
}

// render map based on player position
// make player icon rotate -> means it must be based on direction vector