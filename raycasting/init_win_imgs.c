/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win_imgs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:13:42 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/20 09:16:53 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// also populates raw pixel data of the texture in to the struct
// pixels are 4 bytes 1 for RGBA each
// pixels = width * height * bytes_per_pixel
int	load_textures(mlx_texture_t *texture, char *path)
{
	texture = mlx_load_png(path);
	if (!texture)
	{
		// call error
		free(texture);
		return (-1);
	}
	// texture->pixels = malloc(texture->width * texture->height * texture->bytes_per_pixel);
	// if (!texture->pixels)
	// {
	// 	return (-1);
	// }
	// exit(EXIT_SUCCESS);
	return (0);
}

int	generate_textures(t_game *game)
{
	size_t	i;
	size_t	tex_n;

	tex_n = 4;
	game->texture = malloc(sizeof(mlx_texture_t) * tex_n);
	if (!game->texture)
		return (-1);
	i = 0;
	while (i < tex_n)
	{
		game->texture[i].width = TEX_WIDTH;
		game->texture[i].height = TEX_HEIGHT;
		i++;
	}
	if (load_textures(&game->texture[0], "../assets/doom_22.png") == -1)
	{
		printf("error\n");
		return (-1);
	}
	if (load_textures(&game->texture[1], "../assets/doom_1.png") == -1)
		return (-1);
	if (load_textures(&game->texture[2], "../assets/doom_2.png") == -1)
		return (-1);
	if (load_textures(&game->texture[3], "../assets/doom_3.png") == -1)
		return (-1);
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

// void	img_to_win()
// {

// }

void	init_win_imgs(t_game *game)
{
	// mlx_set_setting(MLX_FULLSCREEN, 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game->mlx = mlx_init(WIDTH, HEIGHT, "game3D", true);
	if (game->mlx == NULL)
	{
		// call custom error function
		printf("Failed to initialize mlx\n");
		exit(EXIT_FAILURE);
	}
	// intialises new Window

	game->width = WIDTH;
	game->height = HEIGHT;
	game->cell_size = 16;
	get_map_size(game); // need x and y size
	// mlx_get_monitor_size(0, &game->width, &game->height);
	printf(MAGENTA"width: %d\n"WHITE, game->width);
	printf(MAGENTA"height: %d\n"WHITE, game->height);
	mlx_set_window_size(game->mlx, game->width, game->height);
	mlx_set_window_pos(game->mlx, 0, 0);

	new_image(game->mlx, &game->map_image, game->map_size.x * game->cell_size, game->map_size.y * game->cell_size);
	new_image(game->mlx, &game->player_image, game->cell_size / 2, game->cell_size / 2);
	new_image(game->mlx, &game->wall_image, game->width, game->height);

	mlx_image_to_window(game->mlx, game->wall_image, 0, 0);
	if (generate_textures(game) == -1)
		return ;

	// mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
}
