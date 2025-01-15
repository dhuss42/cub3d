/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:32:28 by maustel           #+#    #+#             */
/*   Updated: 2025/01/10 10:32:28 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*-------------------------------------------------------------------
	check if everything present (NO, WE, SO, EA, F, C)
-------------------------------------------------------------------*/
static void	check_all_there(t_cub *cub)
{
	if (!cub->assets->no)
		print_error_free_exit(E_MISSING, cub, "'NO' file path\n");
	if (!cub->assets->ea)
		print_error_free_exit(E_MISSING, cub, "'EA' file path\n");
	if (!cub->assets->so)
		print_error_free_exit(E_MISSING, cub, "'SO' file path\n");
	if (!cub->assets->we)
		print_error_free_exit(E_MISSING, cub, "'WE' file path\n");
	if (cub->assets->c > 16777215)
		print_error_free_exit(E_MISSING, cub, "'C' ceiling color\n");
	if (cub->assets->f >16777215)
		print_error_free_exit(E_MISSING, cub, "'F' floor color\n");
}

/*-------------------------------------------------------------------
	check if filename of inputfile is valid
	has to end on '.cub'
-------------------------------------------------------------------*/
void	check_filename_valid(t_cub *cub, char *path)	//somewhere else
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (path[i - 4] != '.' || path[i - 3] != 'c'
		|| path[i - 2] != 'u' || path[i - 1] != 'b')
			print_error_free_exit(E_FILENAME, cub, NULL);
}

/*-------------------------------------------------------------------
	check if file exists and is not directory
-------------------------------------------------------------------*/
void	check_filepath_valid(t_cub *cub, char *file_path)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		print_error_free_exit(errno, cub, file_path);
	if (read(fd, 0, 0) < 0)
		print_error_free_exit(errno, cub, file_path);
	if (close(fd) < 0)
		print_error_free_exit(errno, cub, file_path);
}

/*-------------------------------------------------------------------
	check for any non valid characters in map
	valid characters: 1, 0, N, E, S, W, whitespace, newline
-------------------------------------------------------------------*/
bool	non_valid_char_map(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'E' && c != 'S'
		&& c != 'W' && c != '\n' && c != ' ')
			return(true);
	return (false);
}

/*-------------------------------------------------------------------
	check map for newlines, non valid characters, if player exists
-------------------------------------------------------------------*/
void	check_map_valid(int j, t_cub *cub, char **map)
{
	while(map[j])
	{
		int	i;

		i = 0;
		if (map[j][i] == '\n' && map [j + 1] && map [j + 1][0] != '\n')
			print_error_free_exit(E_NEWLINEMAP, cub, NULL);
		while(map[j][i])
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
			print_error_free_exit(E_MALLOC, cub, NULL);
		i++;
	}
	map_new[i] = NULL;
	return (map_new);
}

/*-------------------------------------------------------------------
	check if map is closed/surrounded by walls
	starting from players position, check always the surrounding fields
	if not beyond map, set it to 1
	if 1, return
	if it reaches beyond the borders of the map ('\0', '\n' or y/x < 0),
	means that map is open
-------------------------------------------------------------------*/
void	floodfill(char **map, t_cub *cub, int x, int y)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x]|| map[y][x] == '\n')
		print_error_free_exit(E_OPENMAP, cub, NULL);
	if (map[y][x] == '1')
		return ;
	else (map[y][x] = '1');
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

	j = 0;
	while (map[j])
	{
		if (map[j][0] == '\n')
		{
			map[j] = NULL;
			while (map[j])
			{
				free(map[j]);
				map[j] = NULL;
				j++;
			}
		}
		j++;
	}
}

/*-------------------------------------------------------------------
	check if map exists, check for any invalid content
-------------------------------------------------------------------*/
void	check_map(char **map, t_cub *cub)
{
	int		j;
	char	**flood_map;

	if (!map || !*map)
		print_error_free_exit(E_NOMAP, cub, NULL);
	j = 0;
	while(map[j][0] == '\n')
		j++;
	check_map_valid(j, cub, map);
	flood_map = cpy_map(map, cub);
	floodfill(flood_map, cub, cub->mapy->player_pos[1], cub->mapy->player_pos[0]);
	free_double(flood_map);
	cut_newlines_map_end(map);
}

/*-------------------------------------------------------------------
	check if parsed input is valid
-------------------------------------------------------------------*/
void	check_content(t_cub *cub)
{
	check_all_there(cub);
	check_filepath_valid(cub, cub->assets->no);
	check_filepath_valid(cub, cub->assets->ea);
	check_filepath_valid(cub, cub->assets->so);
	check_filepath_valid(cub, cub->assets->we);
	check_map(cub->mapy->map, cub);
}
