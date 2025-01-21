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

int	generate_textures(t_cub *cub)
{
	size_t	i;
	size_t	tex_n;

	tex_n = 4;
	cub->texture = malloc(sizeof(mlx_texture_t) * tex_n);
	if (!cub->texture)
		return (-1);
	i = 0;
	while (i < tex_n)
	{
		cub->texture[i].width = TEX_WIDTH;
		cub->texture[i].height = TEX_HEIGHT;
		i++;
	}
	if (load_textures(&cub->texture[0], "../assets/doom_22.png") == -1)
	{
		printf("error\n");
		return (-1);
	}
	if (load_textures(&cub->texture[1], "../assets/doom_1.png") == -1)
		return (-1);
	if (load_textures(&cub->texture[2], "../assets/doom_2.png") == -1)
		return (-1);
	if (load_textures(&cub->texture[3], "../assets/doom_3.png") == -1)
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

void	init_win_imgs(t_cub *cub)
{
	// mlx_set_setting(MLX_FULLSCREEN, 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (cub->mlx == NULL)
	{
		// call custom error function
		printf("Failed to initialize mlx\n");
		exit(EXIT_FAILURE);
	}
	// intialises new Window

	cub->width = WIDTH;
	cub->height = HEIGHT;
	cub->cell_size = 16;
	get_map_size(cub);
	// mlx_get_monitor_size(0, &cub->width, &cub->height);
	printf(MAGENTA"width: %d\n"WHITE, cub->width);
	printf(MAGENTA"height: %d\n"WHITE, cub->height);
	mlx_set_window_size(cub->mlx, cub->width, cub->height);
	mlx_set_window_pos(cub->mlx, 0, 0);

	new_image(cub->mlx, &cub->map_image, cub->map_size.x * cub->cell_size, cub->map_size.y * cub->cell_size);
	new_image(cub->mlx, &cub->player_image, cub->cell_size / 2, cub->cell_size / 2);
	new_image(cub->mlx, &cub->wall_image, cub->width, cub->height);

	if (generate_textures(cub) == -1)
		return ;

	mlx_image_to_window(cub->mlx, cub->wall_image, 0, 0);
	// mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_DISABLED);
}
