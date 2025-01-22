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

void	game_loop(void *param)
{
	t_game	*game;

	game = param;
	ft_key_hook(game);
	reset_img(game->width, game->height, 0xFFC1C1FF, game->wall_image);
	reset_img(game->map_size.x * game->cell_size, game->map_size.y * game->cell_size, 0xFF00FFFF, game->map_image);
	raycaster(game);
	draw_mini_map(game);
	draw_direction(game, game->dir_player.x, game->dir_player.y);
}

void	rendering(t_cub *cub)
{
	t_game game;

	game.map = cub->mapy->map;
	init_win_imgs(&game);
	mini_map(&game);
	game.pos_player.x += 0.5;
	game.pos_player.y += 0.5;
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
}

// int	main()
// {
// 	t_game	game;

// 	char	*map[] = {
// 		"1111111111",
// 		"1000000001",
// 		"1000000001",
// 		"1000000001",
// 		"1000001101",
// 		"10S0000001",
// 		"1000001001",
// 		"1001001001",
// 		"1100001101",
// 		"1111111111",
// 		NULL
// 	};
// 	game.map = map;
// 	visualisation(&game);
// 	return (0);
// }

// tidy up
// handle minimap and screen size more gracefully
// fix minimap x and y checks to be more dynamic
// handle double speed when moving diagonally
// handle minimap colission better

// look into textures

// rotate point of view with mouse
