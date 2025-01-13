/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:55:42 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/13 14:55:22 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	reset_img(t_cub *cub)
{
	int x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH / 2)
		{
			if (x + (WIDTH / 2) > WIDTH / 2 && x + (WIDTH / 2) < WIDTH && y > 0 && y < HEIGHT)
				mlx_put_pixel(cub->map_image, WIDTH / 2 + x, 0 + y, 0xFF808080);
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
	reset_img(cub);
	raycaster(cub);

}

void	visualisation(t_cub *cub)
{
	init_win_imgs(cub);
	mini_map(cub);
	cub->pos_player.x += 0.5;
	cub->pos_player.y += 0.5;
	// raycaster(cub);
	// mlx_loop_hook(cub->mlx, ft_key_hook, cub);
	// handles key presses
	mlx_loop_hook(cub->mlx, game_loop, cub);
	mlx_loop(cub->mlx);
}

int	main()
{
	t_cub   cub;

	char	*map[] = {
		"1111111111",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000001101",
		"1000000001",
		"100000E001",
		"1000000001",
		"1000000101",
		"1111111111",
		NULL
	};
	cub.map = map;
	visualisation(&cub);
	return (0);
}