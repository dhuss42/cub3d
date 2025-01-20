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

#include "raycasting.h"

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
	t_cub	*cub;

	cub = param;
	ft_key_hook(cub);
	reset_img(cub->width, cub->height, 	0xFFC1C1FF, cub->wall_image);
	reset_img(cub->map_size.x * cub->cell_size, cub->map_size.y * cub->cell_size, 0xFF00FFFF, cub->map_image);
	raycaster(cub);
	draw_mini_map(cub);
	draw_direction(cub, cub->dir_player.x, cub->dir_player.y);
}

void	visualisation(t_cub *cub)
{
	init_win_imgs(cub);
	mini_map(cub);
	cub->pos_player.x += 0.5;
	cub->pos_player.y += 0.5;
	mlx_loop_hook(cub->mlx, game_loop, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

int	main()
{
	t_cub	cub;

	char	*map[] = {
		"1111111111",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000001101",
		"10S0000001",
		"1000001001",
		"1001001001",
		"1100001101",
		"1111111111",
		NULL
	};
	cub.map = map;
	visualisation(&cub);
	return (0);
}

// tidy up
// handle minimap and screen size more gracefully
// fix minimap x and y checks to be more dynamic
// handle double speed when moving diagonally
// handle minimap colission better

// look into textures

// rotate point of view with mouse
