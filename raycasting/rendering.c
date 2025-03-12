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

/*----------------------------------------------*/
/* resets the img to a colour passed			*/
/*----------------------------------------------*/
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
				mlx_put_pixel(img, x, y, colour);
			x++;
		}
		y++;
	}
}

/*----------------------------------------------*/
/* loops over:									*/
/* key hook 									*/
/* setting floor and ceiling to diff colours 	*/
/* raycaster									*/
/*----------------------------------------------*/
void	game_loop(void *param)
{
	t_game	*game;

	game = param;
	ft_key_hook(game);
	reset_img(game->width, game->height / 2, game->ass->f, game->wall_image);
	reset_img(game->width, game->height, game->ass->c, game->wall_image);
	raycaster(game);
}

/*----------------------------------------------*/
/* initialise mlx stuff						   	*/
/* set initial player values 					*/
/* set hooks & loop								*/
/* free mlx_stuff								*/
/*----------------------------------------------*/
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
	free_mlx(&game, 0, 0);
}


// with at leaks
//	-> currently more leaks when mlx_terminate is active
//	-> 1 leaks when only free_pngs()

// with system sanitiser
// -> less leaks when mlx_terminate is active (15 leaks)
// -> sometimes segfaults
