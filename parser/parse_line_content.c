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

------------------------------------------------------------------------*/
int	store_path(char **assetpath, char *line, t_assets *assets, char *as)
{
	int	tmp;

	if (*assetpath != NULL)
	{
		assets->err = E_DUPLICATE;
		print_error(E_DUPLICATE, as);
		return (1);
	}
	assets->i = assets->i + 2;
	while (line[assets->i] == ' ' || line[assets->i] == 9)	//jump whitspaces and tabs
		assets->i++;
	tmp = assets->i;
	while (line[assets->i] >= 33 && 126 >= line[assets->i])	//as long as printable characters and no spaces
		assets->i++;
	*assetpath = ft_calloc((assets->i - tmp + 1), sizeof(char));
	if (!*assetpath)
		return (1);	//do something else (exit?)
	assets->i = tmp;
	while (line[assets->i] >= 33 && 126 >= line[assets->i])
	{
		assetpath[0][assets->i - tmp] = line[assets->i];
		assets->i++;
	}

	// printf("%s%s\n", as, *assetpath);
	return (1);
}

int	is_asset(char *line, t_assets *assets)
{
	assets->i = 0;
	while (line[assets->i])
	{
		while (line[assets->i] == ' ' || line[assets->i] == 9)
			assets->i++;
		// printf("%c\n", line[assets->i]);
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
int	is_color(char *line, t_assets *assets)
{
	(void)line;
	(void)assets;
	return (0);
}

int	is_map(char *line, char **map)
{
	(void)line;
	(void)map;
	return (0);
}
