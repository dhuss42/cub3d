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
	if (!cub->assets->c_set)
		print_error_free_exit(E_MISSING, cub, "'C' ceiling color\n");
	if (!cub->assets->f_set)
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
	check if map exists, check for any invalid content
-------------------------------------------------------------------*/
void	check_map(char **map, t_cub *cub)
{
	int		j;
	int		i;
	char	**flood_map;

	if (!map || !*map)
		print_error_free_exit(E_NOMAP, cub, NULL);
	j = 0;
	i = 0;
	while (map[j][0] == '\n')
		j++;
	check_map_valid(i, j, cub, map);
	flood_map = cpy_map(map, cub);
	floodfill(flood_map, cub, cub->mapy->player_pos[1],
		cub->mapy->player_pos[0]);
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
