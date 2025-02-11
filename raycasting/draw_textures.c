/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:54:46 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/11 10:34:59 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	rgba_colours(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	determine_tex_colours(t_game *game, mlx_texture_t *tex, int tex_y)
{
	unsigned int	i;

	i = (tex_y * tex->width + game->texture_x) * 4;
	game->colour = (rgba_colours(tex->pixels[i], tex->pixels[i + 1],
				tex->pixels[i + 2], tex->pixels[i + 3]));
}

// function loops through the vertical line of each point on the x axis
// step: the increment in texture coordinates
// texture_pos is the starting texture coordinate for the current vertical line
//	line_start is the starting y-coordinate of the wall segment on the screen
//	height / 2 Centers the screen vertically
//	line_height centers the wall texture vertically relative to its segment
// y is the vertical screen pixel currently being processed
// texture_y is the corresponding texture y-coordinate
// texture_y = (int)texture_pos & game->texture[game->tex_num]->height;
// -> handles overflow (valid range is 0 to
//		game->texture[game->tex_num]->height)
// -> wraps round
void	loop_y_axis(t_game *game, int x)
{
	float			step;
	float			tex_pos;
	int				y;
	int				tex_y;
	mlx_texture_t	tex;

	step = 1.0 * game->texture[game->tex_num]->height / game->line_height;
	tex_pos = (game->line_start - game->height / 2
			+ game->line_height / 2) * step;
	y = game->line_start;
	tex_y = (int)tex_pos % game->texture[game->tex_num]->height;
	tex = *game->texture[game->tex_num];
	while (y < game->line_end)
	{
		tex_y = (int)tex_pos % tex.height;
		if (tex_y < 0)
			tex_y += tex.height;
		tex_pos += step;
		determine_tex_colours(game, &tex, tex_y);
		if (y > 0 && y < game->height && x > 0 && x < game->width)
			mlx_put_pixel(game->wall_image, x, y, game->colour);
		y++;
	}
}

// scales wall_x with texture width to get exact x-location on texture
// checks which side was hit (vertical/horizontal)
// also checks if right side or bottom was hit
// reverses image if both conditions true
// example texture_x = 50, subtracting it from entire width
//		equals same distance from the end of the image
// -1 accounts for starting at 0
void	scale_to_texture_width(t_game *game)
{
	game->texture_x = game->wall_x * game->texture[game->tex_num]->width;
	if (game->side == 0 && game->ray_dir.x > 0)
	{
		game->texture_x = game->texture[game->tex_num]->width
			- game->texture_x -1;
	}
	if (game->side == 1 && game->ray_dir.y < 0)
	{
		game->texture_x = game->texture[game->tex_num]->width
			- game->texture_x -1;
	}
}

// determines the correct texture depending on the location on the map
// subtracts -1 because texture array start at 0 and Wall is 1 on map
// calculates where the ray hit the wall relative to the map grid
// checks if vertical wall or horizontal
// removes the integral part from the fractional part
// now wall_x is the percentage of the hitpoint on the x-axis of the texture
void	exact_hit_point(t_game *game)
{
	if (game->side == 0)
	{
		game->wall_x = game->pos_player.y + game->plane_wall_dist
			* game->ray_dir.y;
		if (game->ray_dir.x > 0)
			game->tex_num = 2;
		else
			game->tex_num = 3;
	}
	else
	{
		game->wall_x = game->pos_player.x + game->plane_wall_dist
			* game->ray_dir.x;
		if (game->ray_dir.y < 0)
			game->tex_num = 0;
		else
			game->tex_num = 1;
	}
	game->wall_x -= floor(game->wall_x);
}
