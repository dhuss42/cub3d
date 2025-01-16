/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:02 by dhuss             #+#    #+#             */
/*   Updated: 2025/01/16 09:31:20 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

bool	is_player(char c, t_cub *cub)
{
	int		i;
	char	*str;

	i = 0;
	str = "NSEW";
	while (str[i] != '\0')
	{
		if (c == str[i])
		{
			cub->start_dir = c;
			return (true);
		}
		i++;
	}
	return (false);
}

void	get_map_size(t_cub *cub)
{
	int	x;
	int	y;
	int	longest_x;

	y = 0;
	longest_x = 0;
	while (cub->map[y] != NULL)
	{
		x = 0;
		while (cub->map[y][x] != '\0')
		{
			x++;
		}
		if (longest_x < x)
		{
			longest_x = x;
		}
		y++;
	}
	cub->map_size.y = y;
	cub->map_size.x = longest_x;
	printf(GREEN"x = %d\n"WHITE, cub->map_size.x);
	printf(GREEN"y = %d\n"WHITE, cub->map_size.y);
}
