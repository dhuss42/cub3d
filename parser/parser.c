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
	if (is_asset(line, cub->assets))
		return ;
	if (is_color(line, cub->assets))
		return ;
	// is_map(line, cub->map);
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
		print_error_free_exit(errno, NULL, NULL);
	line = get_next_line(fd);
	if (!line)
		print_error_free_exit(E_EMPTYFILE, NULL, NULL);
	while (line)
	{
		parse_line(line, cub);
		free (line);
		line = get_next_line(fd);
	}
	if (line)
		free (line);
	if (close (fd) < 0)
		print_error_free_exit(errno, cub, NULL);
	
	if (cub->assets->err)
		free_exit (cub->assets->err, cub);
}

static void	init_parsing(t_cub *cub)
{
	cub->map = NULL;
	cub->assets = NULL;
	cub->assets = malloc (sizeof(t_assets));
	if (!cub->assets)
		return ;	//do something more reasonable
	cub->assets->no = NULL;
	cub->assets->ea = NULL;
	cub->assets->so = NULL;
	cub->assets->we = NULL;
	cub->assets->c = 0;
	cub->assets->f = 0;
	cub->assets->err = 0;
	cub->assets->i = 0;
}

void	parser(char *cub_file, t_cub *cub)
{
	init_parsing(cub);
	read_file(cub_file, cub);

	// check_content(cub);

}
