/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:13:51 by maustel           #+#    #+#             */
/*   Updated: 2024/12/19 11:13:51 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	parse_line(char *line, t_cub *cub)
{
	if (cub->assets->err || !line)
		return ;
	if (line[0] == '\n' && !cub->mapy->is_map)
		return ;
	if (is_asset(line, cub->assets))
		return ;
	if (is_color(line, cub->assets))
		return ;
	if (is_map(line, cub))
		return ;
	is_nonsense(line, cub);
}

/*------------------------------------------------------------------------
Read input file line by line until the end of file
If any error occurred during reading, it will be printed immediatly,
but the program will finish to read file until the end, before it exits.
In case of error it exits with last error number
------------------------------------------------------------------------*/
static void	read_file(char *cub_file, t_cub *cub)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
		print_error_free_exit(errno, NULL, cub_file);
	line = get_next_line(fd);
	if (!line)
		print_error_free_exit(E_EMPTYFILE, NULL, NULL);
	while (line)
	{
		parse_line(line, cub);
		free (line);
		line = NULL;
		line = get_next_line(fd);
		cub->mapy->nbr_lines++;
	}
	if (line)
		free (line);
	if (close (fd) < 0)
		print_error_free_exit(errno, cub, cub_file);
	if (cub->assets->err)
		free_exit (cub->assets->err, cub);
}

/*------------------------------------------------------------------------
Init all values that are relevant for parsing
16777215 is the max value if all colors are 255
16777216 I need for the check of color is set. because 0 would be white
------------------------------------------------------------------------*/
static void	init_parsing(t_cub *cub)
{
	cub->assets = NULL;
	cub->assets = malloc (sizeof(t_assets));
	if (!cub->assets)
		return ;	//do something more reasonable
	cub->assets->no = NULL;
	cub->assets->ea = NULL;
	cub->assets->so = NULL;
	cub->assets->we = NULL;
	cub->assets->c = 16777216;
	cub->assets->f = 16777216;
	cub->assets->err = 0;
	cub->assets->i = 0;
	cub->mapy = NULL;
	cub->mapy = malloc (sizeof(t_map));
	if (!cub->mapy)
		return ;	//do something more reasonable
	cub->mapy->map = NULL;
	cub->mapy->is_map = false;
	cub->mapy->is_player = false;
	cub->mapy->player_pos[0] = -1;
	cub->mapy->player_pos[1] = -1;
	cub->mapy->nbr_lines = 0;
	cub->mapy->line_start = 0;
	cub->mapy->longest_line = 0;
	cub->mapy->current_line = 0;
	cub->mapy->err = 0;
}

// void print_binary(uint32_t n) {
//     if (n > 0) {
//         print_binary(n / 2);
//     }
//     printf("%d", n % 2);
// }

void	print_map(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map && map[j])
	{
		i = 0;
		while (map[j][i])
		{
			printf("%c", map[j][i]);
			i++;
		}
		j++;
	}

}

void	print_assets(t_assets *assets)
{
	printf("%s\n", assets->no);
	printf("%s\n", assets->ea);
	printf("%s\n", assets->so);
	printf("%s\n", assets->we);
}

void	parser(char *cub_file, t_cub *cub)
{
	init_parsing(cub);
	check_filename_valid(cub, cub_file);
	check_filepath_valid(cub, cub_file);
	read_file(cub_file, cub);
	if (cub->mapy->is_map)
	{
		get_map(cub_file, cub);
		// print_assets(cub->assets);
	}
	check_content(cub);
	// print_map(cub->mapy->map);
	// printf(YELLOW"%d | %d\n", cub->mapy->player_pos[0], cub->mapy->player_pos[1]);
}
