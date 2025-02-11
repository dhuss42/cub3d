/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:34 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/11 11:02:42 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool	is_player(char c, t_game *game)
{
	int		i;
	char	*str;

	i = 0;
	str = "NSEW";
	while (str[i] != '\0')
	{
		if (c == str[i])
		{
			game->start_dir = c;
			return (true);
		}
		i++;
	}
	return (false);
}

void	get_player_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (is_player(game->map[y][x], game) == true)
			{
				game->pos_player.x = x;
				game->pos_player.y = y;
			}
			x++;
		}
		y++;
	}
	game->pos_player.x += 0.5;
	game->pos_player.y += 0.5;
}

void	assigne_angle_dir(t_game *game, float angle, float x, float y)
{
	game->player_angle = angle;
	game->plane.x = x;
	game->plane.y = y;
}

void	determine_dir(t_game *game, char dir)
{
	if (dir == 'N')
		assigne_angle_dir(game, 3 * PI / 2, 0.66, 0);
	else if (dir == 'E')
		assigne_angle_dir(game, 0, 0, 0.66);
	else if (dir == 'S')
		assigne_angle_dir(game, PI / 2, -0.66, 0);
	else if (dir == 'W')
		assigne_angle_dir(game, PI, 0, -0.66);
	game->dir_player.x = cos(game->player_angle);
	game->dir_player.y = sin(game->player_angle);
}

// finds starting position and angle of player
int	set_player(t_game *game)
{
	get_player_pos(game);
	determine_dir(game, game->start_dir);
	return (0);
}
