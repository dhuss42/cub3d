/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:02 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/07 11:11:19 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

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

void	get_map_size(t_game *game)
{
	int	x;
	int	y;
	int	longest_x;

	y = 0;
	longest_x = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			is_player(game->map[y][x], game);
			x++;
		}
		if (longest_x < x)
		{
			longest_x = x;
		}
		y++;
	}
	game->map_size.y = y;
	game->map_size.x = longest_x;
}
