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

// create a dot at player position
// create vector for looking direction
// move dot when keys are pressed
//  update position of player
// make rotation able

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
	printf(RED"dir player.x: %f /\n"WHITE, game->dir_player.x);
	printf(RED"dir player.y: %f /\n"WHITE, game->dir_player.y);
}


// If the player is facing East (0°), cos(0) gives 1 (along the x-axis), and sin(0) gives 0 (along the y-axis).
// So, the direction vector is (1, 0), which points straight to the right.

void	determine_plane(t_game *game)
{
	t_vector	camera;

	camera = game->plane;
	camera.x = game->dir_player.y;
	camera.y = game->dir_player.x;
	printf(RED"camera.x %f\n"WHITE, camera.x);
	printf(RED"camera.y %f\n"WHITE, camera.y);
	printf(GREEN"dir_player.x %f\n"WHITE, game->dir_player.x);
	printf(GREEN"dir_player.y %f\n"WHITE, game->dir_player.y);


	// inverse of direction vector
	// needs to be variable based on the starting direction
}

// finds starting position and angle of player
int	create_vectors(t_game *game)
{
	// printf("char dir: %c\n", game->start_dir);
	game->pos_player = find_position(game->map, game->start_dir);
	determine_dir(game, game->start_dir);
	determine_plane(game);
	return (0);
}
