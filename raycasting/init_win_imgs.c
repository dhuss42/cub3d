/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win_imgs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:13:42 by dhuss             #+#    #+#             */
/*   Updated: 2025/03/11 12:25:28 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*----------------------------------------------*/
/* loads the different textures 				*/
/*----------------------------------------------*/
int	load_textures(t_game *game)
{
	t_assets	*assets;

	assets = game->ass;
	game->texture[0] = mlx_load_png(assets->no);
	if (!game->texture[0])
		return (-1);
	game->texture[1] = mlx_load_png(assets->so);
	if (!game->texture[1])
		return (-1);
	game->texture[2] = mlx_load_png(assets->ea);
	if (!game->texture[2])
		return (-1);
	game->texture[3] = mlx_load_png(assets->we);
	if (!game->texture[3])
		return (-1);
	return (0);
}

/*----------------------------------------------*/
/* initialise mlx stuff						   	*/
/* 	-> mlx instance								*/
/*	-> image									*/
/*	-> porject img to window					*/
/* 	-> textures									*/
/*----------------------------------------------*/
void	init_win_imgs(t_game *game)
{
	game->width = WIDTH;
	game->height = HEIGHT;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game->mlx = mlx_init(game->width, game->height, "game3D", true);
	if (!game->mlx)
		print_error_free_exit(E_MLXINIT, game->cub, NULL);
	game->wall_image = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->wall_image)
		free_mlx(game, E_MLXIMG, 1);
	if (mlx_image_to_window(game->mlx, game->wall_image, 0, 0) == -1)
		free_mlx(game, E_MLXIMGTOWIN, 1);
	if (load_textures(game) == -1)
		free_mlx(game, E_MLXLOADPNG, 1);
}
