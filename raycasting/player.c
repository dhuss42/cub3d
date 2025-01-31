/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:34 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/20 09:49:05 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_vector	find_position(char **map, char identifier)
{
	int y;
	int x;
	t_vector pos;

	pos.x = -1;
	pos.y = -1;
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == identifier)
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
			x++;
		}
		y++;
	}
	return (pos);
}

void	determine_dir(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player_angle = 3 * PI / 2; // turned around because of y
		game->plane.x = 0.66;
		game->plane.y = 0;
	}
	else if (dir == 'E')
	{
		game->player_angle = 0;
		game->plane.x = 0;
		game->plane.y = 0.66;
	}
	else if (dir == 'S')
	{
		game->player_angle = PI / 2;
		game->plane.x = -0.66;
		game->plane.y = 0;
	}
	else if (dir == 'W')
	{
		game->player_angle = PI;
		game->plane.x = 0;
		game->plane.y = -0.66;
	}
	game->dir_player.x = cos(game->player_angle);
	game->dir_player.y = sin(game->player_angle);
}

// finds starting position and angle of player
int	set_player(t_game *game)
{
	get_map_size(game); // determines NSWO right now
	// is used for out of bounds check when moving, but the x and y sizes of the map are only accurate when map is a rectangle
	game->pos_player = find_position(game->map, game->start_dir);
	game->pos_player.x += 0.5;
	game->pos_player.y += 0.5;
	determine_dir(game, game->start_dir);
	return (0);
}
