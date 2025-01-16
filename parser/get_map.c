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

/*------------------------------------------------------------------------
Double array map is allocated
Each string of it is allocated with the longest line-length of the map
------------------------------------------------------------------------*/
void	allocate_map(t_map *mapy)
{
	int	i;

	mapy->map = malloc(sizeof(char*) * (mapy->nbr_lines - mapy->line_start + 1));
	if (!mapy->map)
	{
		print_error(E_MALLOC, &mapy->err, NULL);
		return ;
	}
	i = 0;
	while (i < (mapy->nbr_lines - mapy->line_start))
	{
		mapy->map[i] = NULL;
		mapy->map[i] = malloc (sizeof(char) * (mapy->longest_line + 1));
		if (!mapy->map[i])
		{
			print_error(E_MALLOC, &mapy->err, NULL);
			return ;
		}
		i++;
	}
}

/*------------------------------------------------------------------------
copy line to corresponding map-line
------------------------------------------------------------------------*/
void	write_to_map(char *line, t_map *mapy)
{
	int	i;

	if (!mapy->map)
		allocate_map(mapy);
	if (mapy->err)
		return ;
	if (!mapy->map[mapy->current_line])
	{
		print_error(E_MALLOC, &mapy->err, NULL);
		return ;
	}
	i = 0;
	while (line[i])
	{
		mapy->map[mapy->current_line][i] = line[i];
		i++;
	}
	mapy->map[mapy->current_line][i] = '\0';
	mapy->current_line++;
	if (mapy->current_line == (mapy->nbr_lines - mapy->line_start))
		mapy->map[mapy->current_line] = NULL;
}

/*------------------------------------------------------------------------
Use getnextline again to get the map
------------------------------------------------------------------------*/
void	get_map(char *cub_file, t_cub *cub)
{
	int		fd;
	int		i;

	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
		print_error_free_exit(errno, NULL, NULL);
	cub->mapy->line = get_next_line(fd);
	if (!cub->mapy->line)
		print_error_free_exit(E_EMPTYFILE, NULL, NULL);
	i = 0;
	while (cub->mapy->line)
	{
		if (i >= cub->mapy->line_start)
			write_to_map(cub->mapy->line, cub->mapy);
		free (cub->mapy->line);
		cub->mapy->line = NULL;
		cub->mapy->line = get_next_line(fd);
		i++;
	}
	if (cub->mapy->line)
		free (cub->mapy->line);
	if (close (fd) < 0)
		print_error_free_exit(errno, cub, NULL);
	if (cub->mapy->err)
		free_exit (cub->mapy->err, cub);
}
