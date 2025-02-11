/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win_imgs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:13:42 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/07 11:11:33 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	load_textures(t_game *game)
{
	t_assets	*assets;

	assets = game->ass;
	game->texture[0] = mlx_load_png(assets->no);
	if (!game->texture[0])
		print_error_free_exit(E_MLXLOADPNG, game->cub, assets->no);
	game->texture[1] = mlx_load_png(assets->so);
	if (!game->texture[1])
		print_error_free_exit(E_MLXLOADPNG, game->cub, assets->so);
	game->texture[2] = mlx_load_png(assets->ea);
	if (!game->texture[2])
		print_error_free_exit(E_MLXLOADPNG, game->cub, assets->ea);
	game->texture[3] = mlx_load_png(assets->we);
	if (!game->texture[3])
		print_error_free_exit(E_MLXLOADPNG, game->cub, assets->we);
	return (0);
}

void	init_win_imgs(t_game *game)
{
	game->width = WIDTH;
	game->height = HEIGHT;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game->mlx = mlx_init(game->width, game->height, "game3D", true);
	if (!game->mlx)
		print_error_free_exit(E_MLXINIT, game->cub, NULL);
	game->wall_image = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->mlx)
		print_error_free_exit(E_MLXIMG, game->cub, NULL);
	if (mlx_image_to_window(game->mlx, game->wall_image, 0, 0) == -1)
		print_error_free_exit(E_MLXIMGTOWIN, game->cub, NULL);
	load_textures(game);
}
