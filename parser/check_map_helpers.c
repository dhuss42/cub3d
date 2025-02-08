/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:53:33 by maustel           #+#    #+#             */
/*   Updated: 2025/01/16 13:53:33 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*-------------------------------------------------------------------
check for any non valid characters in map
valid characters: 1, 0, N, E, S, W, whitespace, newline
-------------------------------------------------------------------*/
bool	non_valid_char_map(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'E' && c != 'S'
		&& c != 'W' && c != '\n' && c != ' ')
		return (true);
	return (false);
}

/*-------------------------------------------------------------------
check map for newlines, non valid characters, if player exists
-------------------------------------------------------------------*/
void	check_map_valid(int i, int j, t_cub *cub, char **map)
{
	while (map[j])
	{
		i = 0;
		if (map[j][i] == '\n' && map [j + 1] && map [j + 1][0] != '\n')
			print_error_free_exit(E_NEWLINEMAP, cub, NULL);
		while (map[j][i])
		{
			if (non_valid_char_map(map[j][i]))
				print_error_free_exit(E_LINECONTENT, cub, map[j]);
			if (map[j][i] == 'N' || map[j][i] == 'E'
				|| map[j][i] == 'S' || map[j][i] == 'W')
			{
				if (cub->mapy->is_player)
					print_error_free_exit(E_TOOMANYPLAYERS, cub, map[j]);
				cub->mapy->is_player = true;
				cub->mapy->player_pos[0] = j;
				cub->mapy->player_pos[1] = i;
			}
			i++;
		}
		j++;
	}
	if (!cub->mapy->is_player)
		print_error_free_exit(E_NOPLAYER, cub, map[j]);
}

/*-------------------------------------------------------------------
copy map to do floodfill
-------------------------------------------------------------------*/
char	**cpy_map(char **map_2d, t_cub *cub)
{
	char	**map_new;
	int		i;

	i = 0;
	while (map_2d[i])
		i++;
	map_new = malloc (sizeof(char *) * (i + 1));
	if (!map_new)
		print_error_free_exit(E_MALLOC, cub, NULL);
	i = 0;
	while (map_2d[i])
	{
		map_new[i] = ft_strdup(map_2d[i]);
		if (!map_new[i])
		{
			free_double(map_new);
			print_error_free_exit(E_MALLOC, cub, NULL);
		}
		i++;
	}
	map_new[i] = NULL;
	return (map_new);
}

/*-------------------------------------------------------------------
check if map is closed/surrounded by walls
starting from players position, check always the surrounding fields
if not beyond map, set it to 2
if 1 or 2, return
if it reaches beyond the borders of the map ('\0', '\n' or y/x < 0),
means that map is open
-------------------------------------------------------------------*/
void	floodfill(char **map, t_cub *cub, int x, int y)
{
	if (y < 0 || x < 0 || !map[y] || x > (int)ft_strlen(map[y])
		|| !map[y][x] || map[y][x] == '\n')
	{
		free_double(map);
		print_error_free_exit(E_OPENMAP, cub, NULL);
	}
	if (map[y][x] == '1' || map[y][x] == '2')
		return ;
	// check_edge(map, cub, x, y);
	(map[y][x] = '2');
	floodfill(map, cub, x, y + 1);
	floodfill(map, cub, x, y - 1);
	floodfill(map, cub, x + 1, y);
	floodfill(map, cub, x - 1, y);
}

/*-------------------------------------------------------------------
remove all lines including only '\n' from map`s end
-------------------------------------------------------------------*/
void	cut_newlines_map_end(char **map)
{
	int	j;
	int	f;

	j = 0;
	f = 0;
	while (map[j])
	{
		if (map[j][0] == '\n')
			f = j;
		j++;
	}
	while (j <= f)
	{
		free(map[j]);
		map[j] = NULL;
		j--;
	}
}

/*-------------------------------------------------------------------
check if map is closed/surrounded by walls
starting from players position, check always the surrounding fields
if not beyond map, set it to 1
if 1, return
if it reaches beyond the borders of the map ('\0', '\n' or y/x < 0),
means that map is open
-------------------------------------------------------------------*/
// void	floodfill(char **map, t_cub *cub, int x, int y)
// {
// 	if (y < 0 || x < 0 || !map[y] || x > (int)ft_strlen(map[y])
// 		|| !map[y][x] || map[y][x] == '\n')
// 	{
// 		free_double(map);
// 		print_error_free_exit(E_OPENMAP, cub, NULL);
// 	}
// 	if (map[y][x] == '1')
// 		return ;
// 	else
// 		(map[y][x] = '1');
// 	floodfill(map, cub, x, y + 1);
// 	floodfill(map, cub, x, y - 1);
// 	floodfill(map, cub, x + 1, y);
// 	floodfill(map, cub, x - 1, y);
// }
