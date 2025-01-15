/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win_imgs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:13:42 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/14 15:05:34 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	new_image(mlx_t *mlx, mlx_image_t **image, uint32_t width, uint32_t height)
{
	*image = mlx_new_image(mlx, width, height);
	if (image == NULL)
	{
		// call custom error function
		printf("Failed to create image\n");
		exit(EXIT_FAILURE);
	}
}

void	init_win_imgs(t_cub *cub)
{
	mlx_set_setting(MLX_FULLSCREEN, 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (cub->mlx == NULL)
	{
		// call custom error function
		printf("Failed to initialize mlx\n");
		exit(EXIT_FAILURE);
	}
	// intialises new Window

	// int width = 0;
	// int	height = 0;
	// mlx_get_monitor_size(0, &width, &height);
	// printf(MAGENTA"width: %d\n"WHITE, width);
	// printf(MAGENTA"height: %d\n"WHITE, height);

	cub->width = 0;
	cub->height = 0;
	mlx_get_monitor_size(0, &cub->width, &cub->height);
	printf(MAGENTA"width: %d\n"WHITE, cub->width);
	printf(MAGENTA"height: %d\n"WHITE, cub->height);
	mlx_set_window_size(cub->mlx, cub->width, cub->height);
	mlx_set_window_pos(cub->mlx, 0, 0);
	new_image(cub->mlx, &cub->map_image, cub->width, cub->height);
	new_image(cub->mlx, &cub->player_image, 32, 32);
}
