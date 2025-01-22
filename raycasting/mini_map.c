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

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			start_x = x * game->cell_size;
			start_y = y * game->cell_size;
			// determines where to start drawing
			if (game->map[y][x] == '1')
				draw_cell(game->map_image, start_x, start_y, game->cell_size - 1, 0x000000FF, game);
			else if (game->map[y][x] == '0')
				draw_cell(game->map_image, start_x, start_y, game->cell_size - 1, 0xFFFFFFFF, game);
			else if (is_player(game->map[y][x], game))
				draw_cell(game->map_image, start_x, start_y, game->cell_size - 1, 0xFFFFFFFF, game);
			else
				draw_cell(game->map_image, start_x, start_y, game->cell_size, 0x00000000, game);
			x++;
		}
		y++;
	}
	// interates over map and draws cells according to 1 and 0
	// displays image on window at x = 0 and y = 0
	// create_vectors(game);
}

void	mini_map(t_game *game)
{
	// printf("test0\n");
	draw_mini_map(game);
	mlx_image_to_window(game->mlx, game->map_image, 0, 0);
	// printf("test2\n");
	create_vectors(game);
	// printf("test3\n");
	draw_player(game);
	// printf("test4\n");
}
