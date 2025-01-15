/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:21 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/14 14:43:56 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// make cleaner by centring pos_player
// include error checks
// make screen size more flexible

void	draw_mini_map(t_cub *cub)
{
	int	x;
	int	y;
	int	cell_size;
	int	start_x;
	int	start_y; // The actual pixel location on the window (map location * cell_size)

	cell_size = 64;
	y = 0;
	while (cub->map[y] != NULL)
	{
		x = 0;
		while (cub->map[y][x] != '\0')
		{
			start_x = x * cell_size;
			start_y = y * cell_size;
			// determines where to start drawing
			if (cub->map[y][x] == '1')
				draw_cell(cub->map_image, start_x, start_y, cell_size - 1, 0x000000FF);
			else if (cub->map[y][x] == '0')
				draw_cell(cub->map_image, start_x, start_y, cell_size - 1, 0xFFFFFFFF);
			else if (is_player(cub->map[y][x], cub))
				draw_cell(cub->map_image, start_x, start_y, cell_size - 1, 0xFFFFFFFF);
			else
				draw_cell(cub->map_image, start_x, start_y, cell_size, 0x00000000);
			x++;
		}
		y++;
	}
	// interates over map and draws cells according to 1 and 0
	// displays image on window at x = 0 and y = 0
	// create_vectors(cub);
}

void	mini_map(t_cub *cub)
{
	printf("test0\n");
	draw_mini_map(cub);
	mlx_image_to_window(cub->mlx, cub->map_image, 0, 0);
	printf("test2\n");
	create_vectors(cub);
	printf("test3\n");
	draw_player(cub);
	printf("test4\n");
}
