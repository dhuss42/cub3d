/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:10:36 by maustel           #+#    #+#             */
/*   Updated: 2024/12/19 17:10:36 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*------------------------------------------------------------------------
Detect unexpected content in line
------------------------------------------------------------------------*/
void	check_rest_line(t_assets *assets, char *line)
{
	while(line[assets->i] && line[assets->i] != '\n')
	{
		if (line[assets->i] != 9 && line[assets->i] != ' ')
		{
			assets->err = E_LINECONTENT;
			print_error(E_LINECONTENT, line);
			return ;
		}
		assets->i++;
	}
}

/*------------------------------------------------------------------------
Store path of NO/EA/SO/WE asset into assets->no/ea/so/we
If duplicate detected, print error, store last errornumber
and end program after finishing reading with gnl
Between NO and path: jump whitspaces and tabs
then read until whitspace or non printable character
------------------------------------------------------------------------*/
static int	store_path(char **assetpath, char *line, t_assets *assets, char *as)
{
	int	tmp;

	if (*assetpath != NULL)
	{
		assets->err = E_DUPLICATE;
		print_error(E_DUPLICATE, as);
		return (1);
	}
	assets->i = assets->i + 2;
	while (line[assets->i] == ' ' || line[assets->i] == 9)
		assets->i++;
	tmp = assets->i;
	while (line[assets->i] >= 33 && 126 >= line[assets->i])
		assets->i++;
	*assetpath = ft_calloc((assets->i - tmp + 1), sizeof(char));
	if (!*assetpath)
		return (1);	//do something else (exit?)(printerror?)
	assets->i = tmp;
	while (line[assets->i] >= 33 && 126 >= line[assets->i])
	{
		assetpath[0][assets->i - tmp] = line[assets->i];
		assets->i++;
	}
	check_rest_line(assets, line);
	return (1);
}

/*------------------------------------------------------------------------
Check if in this line is stored assetpath (NO/EA/SO/WE)
in the beginning: skip all whitespaces and tabs
If yes, store it in struct
------------------------------------------------------------------------*/
int	is_asset(char *line, t_assets *assets)
{
	assets->i = 0;
	while (line[assets->i])
	{
		while (line[assets->i] == ' ' || line[assets->i] == 9)
			assets->i++;
		if (line[assets->i] == 'N' && line[assets->i + 1] == 'O')
			return (store_path(&assets->no, line, assets, "NO"));
		else if (line[assets->i] == 'E' && line[assets->i+1] == 'A')
			return (store_path(&assets->ea, line, assets, "EA"));
		else if (line[assets->i] == 'S' && line[assets->i+1] == 'O')
			return (store_path(&assets->so, line, assets, "SO"));
		else if (line[assets->i] == 'W' && line[assets->i+1] == 'E')
			return (store_path(&assets->we, line, assets, "WE"));
		assets->i++;
	}
	return (0);
}

/*------------------------------------------------------------------------
Check if in this line is stored color (C/F)
in the beginning: skip all whitespaces and tabs
If yes, transform colors to uint32 and store it in struct
------------------------------------------------------------------------*/
int	is_color(char *line, t_assets *assets)
{
	assets->i = 0;
	while (line[assets->i])
	{
		while (line[assets->i] == ' ' || line[assets->i] == 9)
			assets->i++;
		if (line[assets->i] == 'C' || line[assets->i] == 'F')
		{
			if (line[assets->i] == 'C')
				assets->c = color_to_uint32(assets, line);
			else if (line[assets->i] == 'F')
				assets->f = color_to_uint32(assets, line);
			return (1);
		}
		assets->i++;
	}
	return (0);
}

int	is_map(char *line, t_cub *cub)
{
	int	i;

	if (cub->assets->no && cub->assets->ea && cub->assets->so
		&& cub->assets->we && cub->assets->c < 16777216 && cub->assets->f < 16777216)
	{
		if (!cub->mapy->is_map)
		{
			cub->mapy->is_map = true;
			cub->mapy->line_start = cub->mapy->nbr_lines;
		}
		i = 0;
		while (line[i])
			i++;
		if (i > cub->mapy->longest_line)
			cub->mapy->longest_line = i;
		return (1);
	}
	return (0);
}
