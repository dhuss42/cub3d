/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:40:30 by maustel           #+#    #+#             */
/*   Updated: 2025/01/09 12:40:30 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	allocate_map(t_map *mapy)
{
	int	i;

	mapy->map = malloc(sizeof(char*) * (mapy->nbr_lines - mapy->line_start));
	if (!mapy->map)
	{
		mapy->err = E_MALLOC;
		print_error(E_MALLOC, NULL);
		return ;
	}
	i = 0;
	while (i <= (mapy->nbr_lines - mapy->line_start))
	{
		mapy->map[i] = NULL;
		mapy->map[i] = malloc (sizeof(char) * (mapy->longest_line * 1));
		if (!mapy->map[i])
		{
			mapy->err = E_MALLOC;
			print_error(E_MALLOC, NULL);
			return ;
		}
		i++;
	}
}

void	write_to_map(char *line, t_map *mapy)
{
	int	i;

	if (!mapy->map)
		allocate_map(mapy);
	if (mapy->err)
		return ;
	i = 0;
	while (line[i])
	{
		mapy->map[mapy->current_line][i] = line[i];
		i++;
	}
	mapy->map[mapy->current_line][i] = '\0';
	printf(BLUE"CURRENT LINE:%d\n"RESET, mapy->current_line);
	mapy->current_line++;
	// if (mapy->current_line == (mapy->nbr_lines - mapy->line_start + 1))
	// 	mapy->map[mapy->current_line] = NULL;
}

void	get_map(char *cub_file, t_cub *cub)
{
	int		fd;
	int		i;
	char	*line;

	line = NULL;
	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
		print_error_free_exit(errno, NULL, NULL);
	line = get_next_line(fd);
	if (!line)
		print_error_free_exit(E_EMPTYFILE, NULL, NULL);
	i = 0;
	while (line)
	{
		printf(YELLOW"i: %d\n"RESET, i);
		if (i >= cub->mapy->line_start)
			write_to_map(line, cub->mapy);
		printf(RED"HERE\n"RESET);
		free (line);
		line = NULL;
		line = get_next_line(fd);
		i++;
	}
	if (line)
		free (line);
	cub->mapy->map[cub->mapy->current_line] = NULL;
	if (close (fd) < 0)
		print_error_free_exit(errno, cub, NULL);
	if (cub->mapy->err)	//needed? if yes change to mapy->err
		free_exit (cub->mapy->err, cub);
}
