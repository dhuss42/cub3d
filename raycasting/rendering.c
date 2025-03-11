/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:55:42 by dhuss             #+#    #+#             */
/*   Updated: 2025/03/11 14:39:52 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	reset_img(int width, int height, uint32_t colour, mlx_image_t *img)
{
	int	x;
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

void	game_loop(void *param)
{
	t_game	*game;

	game = param;
	ft_key_hook(game);
	reset_img(game->width, game->height / 2, game->ass->f, game->wall_image);
	reset_img(game->width, game->height, game->ass->c, game->wall_image);
	raycaster(game);
}

void	free_pngs(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture[i])
			mlx_delete_texture(game->texture[i]);
		i++;
	}
}

void	rendering(t_cub *cub)
{
	t_game	game;

	game.map = cub->mapy->map;
	game.ass = cub->assets;
	game.cub = cub;
	cub->game = &game;
	init_win_imgs(&game);
	set_player(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_pngs(&game);
	if (game.wall_image)
	{
		mlx_delete_image(game.mlx, game.wall_image);
		game.wall_image = NULL;
	}
	// printf("test\n");
	if (game.mlx)
	{
		mlx_terminate(game.mlx);
		game.mlx = NULL;
	}
	cub->game = NULL;
	// printf("test1\n");
}
