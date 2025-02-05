/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edges.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:58:10 by maustel           #+#    #+#             */
/*   Updated: 2025/02/05 14:58:10 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_outer_edge(char **map, t_cub *cub, int x, int y)
{
	if (map[y][x] != '1')
	{
		free_double(map);
		print_error_free_exit(E_OPENMAP, cub, NULL);
	}
}

void	check_edge(char **map, t_cub *cub, int x, int y)
{
	if (y - 1 < 0 || x - 1 < 0
		|| !map[y + 1] || x + 1 > (int)ft_strlen(map[y])
		|| !map[y][x] || map[y][x + 1] == '\n'
		|| map[y + 1][x] == '\n' || map[y - 1][x] == '\n')
		return ;
	if (map[y + 1][x] == '1' && map[y][x + 1] == '1')
		check_outer_edge(map, cub, x + 1, y + 1);
	if (map[y][x + 1] == '1' && map[y - 1][x] == '1')
		check_outer_edge(map, cub, x + 1, y - 1);
	if (map[y - 1][x] == '1' && map[y][x - 1] == '1')
		check_outer_edge(map, cub, x - 1, y - 1);
	if (map[y][x - 1] == '1' && map[y + 1][x] == '1')
		check_outer_edge(map, cub, x - 1, y + 1);
}
