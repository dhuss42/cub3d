/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win_imgs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:13:42 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/30 10:18:01 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	generate_textures(t_game *game)
{
	game->texture[0] = mlx_load_png(game->ass->no);
	if (!game->texture[0])
		printf("error\n"); // call error function
	game->texture[1] = mlx_load_png(game->ass->so);
	if (!game->texture[1])
		printf("error\n"); // call error function
	game->texture[2] = mlx_load_png(game->ass->ea);
	if (!game->texture[2])
		printf("error\n"); // call error function
	game->texture[3] = mlx_load_png(game->ass->we);
	if (!game->texture[3])
		printf("error\n"); // call error function

	// printf("%d\n", game->texture[0]->height);
	// printf("%d\n", game->texture[0]->width);
	return (0);
}

void	new_image(mlx_t *mlx, mlx_image_t **image, uint32_t width, uint32_t height)
{
	*image = mlx_new_image(mlx, width, height);
	if (image == NULL)
	{
		// call custom error function
		printf("Failed to create image\n");
		exit(EXIT_FAILURE);
	}
	// needs to return
}

void	init_win_imgs(t_game *game)
{
	// mlx_set_setting(MLX_FULLSCREEN, 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game->mlx = mlx_init(WIDTH, HEIGHT, "game3D", true);
	if (game->mlx == NULL)
	{
		// call custom error function
		printf("Failed to initialize mlx\n");
		return ;
	}
	game->width = WIDTH;
	game->height = HEIGHT;
	get_map_size(game); // determines NSWO right now

	// mlx_set_window_size(game->mlx, game->width, game->height);

	new_image(game->mlx, &game->player_image, game->cell_size / 2, game->cell_size / 2);
	new_image(game->mlx, &game->wall_image, game->width, game->height);

	mlx_image_to_window(game->mlx, game->wall_image, 0, 0);
	if (generate_textures(game) == -1)
		return ;

	// mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
}
