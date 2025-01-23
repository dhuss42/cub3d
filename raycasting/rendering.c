/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:55:42 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/20 09:51:35 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	reset_img(int width, int height, uint32_t colour, mlx_image_t *img)
{
	int x;
	int	y;

	if (height == HEIGHT)
		y = height / 2;
	else
		y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (y >= 0 && y < height && x >= 0 && x < width)
				mlx_put_pixel(img, x, 0 + y, colour);
			x++;
		}
		y++;
	}
}

void	reset_img_f(int width, int height, uint32_t colour, mlx_image_t *img)
{
	int x;
	int	y;

	y = height / 2;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (y >= 0 && y < height&& x >= 0 && x < width)
				mlx_put_pixel(img, x, 0 + y, colour);
			x++;
		}
		y++;
	}
}

void	game_loop(void *param)
{
	t_game	*game;

	game = param;
	ft_key_hook(game);
	// reset_img(game->width, game->height, 0xFFC1C1FF, game->wall_image);
	reset_img(game->width, game->height / 2, game->ass->f, game->wall_image);
	reset_img(game->width, game->height, game->ass->c, game->wall_image);

	// reset_img(game->map_size.x * game->cell_size, game->map_size.y * game->cell_size, 0xFF00FFFF, game->map_image);
	// reset_img(game->width / 4, game->height / 4, 0xFF00FFFF, game->map_image); // pink
	reset_img(game->m_map_size.x, game->m_map_size.y, 0xCCCCCCFF, game->map_image); // transparent set last values to 00
	raycaster(game);

	draw_mini_map(game);
	draw_direction(game, game->dir_player.x, game->dir_player.y);
}

void	rendering(t_cub *cub)
{
	t_game game;

	game.map = cub->mapy->map;
	game.ass = cub->assets;
	init_win_imgs(&game);
	mini_map(&game);
	game.pos_player.x += 0.5;
	game.pos_player.y += 0.5;
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
}

// tidy up
// minimap should be rendered only partially and the img window should have a fixed size
// handle minimap colission better
// handle double speed when moving diagonally

// rotate point of view with mouse

// some maps segfault

// map size
//	map size img should be proportional to the Screen width/height

//	map should be rendered new for every movement
//	also player (maybe even rotated player)