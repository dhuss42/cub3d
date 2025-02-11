/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:32:58 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/11 16:05:24 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"


// currently drawing relative to img not to player
void	draw_cells(t_game *game, int start_x, int start_y, uint32_t color)
{
	int	x;
	int y;
	// cell = game->cell_size - 1;
	y = start_y;
	x = start_x;
	// printf("y : %d\n", y);
	// printf("x : %d\n", x);
	while (y < start_y + game->cell_size)
	{
		x = start_x;
		while (x < start_x + game->cell_size)
		{
			if (x >= 0 && y >= 0 && x < game->m_map_size.x && y < game->m_map_size.y)
				mlx_put_pixel(game->map_image, x, y, color);
			x++;
		}
		y++;
	}
}

// iterate from elft most corner to right most corner bound by render distance
// scale with cell size
void	render_map(t_game *game, int start_x, int start_y, int start_px_x, int start_px_y)
{
	int	y;
	int	x;
	int	px;

	y = start_y; // grid coordinates
	x = start_x;
	while (y < floor(game->pos_player.y + game->mini_map.rndr_dst)) // y is left top corner and pos player.y + rndr dst is left bottom
	{
		x = start_x;
		px = start_px_x;
		while (x < floor(game->pos_player.x + game->mini_map.rndr_dst))
		{
			if (game->map[y][x] == '1')
				draw_cells(game, px, start_px_y, 0x000000FF);
			else if (game->map[y][x] != '1')
				draw_cells(game, px, start_px_y, 0xFFFFFFFF);
			x++;
			px += game->cell_size;
		}
		y++;
		start_px_y += game->cell_size;
	}
}

// get left most corner to render
void	get_render_cordinates(t_game *game)
{
	int	start_render_x;
	int	start_render_y;
	int	start_px_x;
	int	start_px_y;

	start_px_x = game->m_map_size.x / 2 - game->mini_map.rndr_dst * game->cell_size; // get left side in px
	start_px_y = game->m_map_size.y / 2 - game->mini_map.rndr_dst * game->cell_size; // get left corner in px
	start_render_x = (int)(game->pos_player.x - game->mini_map.rndr_dst);
	start_render_y = (int)(game->pos_player.y - game->mini_map.rndr_dst);
	if (start_render_x < 0) // also need to check if it's bigger than entire line
		start_render_x = 0;
	if (start_render_y < 0)
		start_render_y = 0;

	if (start_px_x < 0)
		start_px_x = 0;
	if (start_px_y < 0)
		start_px_y = 0;

	printf(RED"pos_player.x : %f\n"WHITE, game->pos_player.x);
	printf(RED"pos_player.y : %f\n"WHITE, game->pos_player.y);
	printf(CYAN"player.x on img %d\n", game->m_map_size.x / 2);
	printf(CYAN"player.y on img %d\n", game->m_map_size.y / 2);
	printf(MAGENTA"start_render_x: %d\n"WHITE, start_render_x);
	printf(MAGENTA"start_render_y: %d\n"WHITE, start_render_y);
	printf(GREEN"start_px_x: %d\n"WHITE, start_px_x);
	printf(GREEN"start_px_y: %d\n"WHITE, start_px_y);
	render_map(game, start_render_x, start_render_y, start_px_x, start_px_y);
}

void	test_draw(t_game *game)
{
	mlx_put_pixel(game->map_image, game->m_map_size.x / 2, game->m_map_size.y / 2, 0xFF0000FF);
}

void	map(t_game *game)
{
	game->mini_map.rndr_dst = 4;
	game->cell_size = 32;
	get_render_cordinates(game);
	test_draw(game);
}

