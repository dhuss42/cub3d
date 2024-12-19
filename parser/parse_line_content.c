/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:10:36 by maustel           #+#    #+#             */
/*   Updated: 2024/12/19 17:10:36 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	write_to_assetfile(char *assetfile, char *content, t_assets *assets, char *ass)
{
	int	tmp;

	if (assetfile != NULL)
	{
		assets->err = E_DUPLICATE;
		print_error(E_DUPLICATE, ass);
		return (1);
	}
	tmp = assets->i;
	while (content[assets->i] >= 33 && 126 >= content[assets->i])
		assets->i++;
	assetfile = malloc(sizeof(char) * (assets->i - tmp + 1));
	if (!assetfile)
		return (1);	//do something else (exit?)
	assets->i = tmp;
	while (content[assets->i] >= 33 && 126 >= content[assets->i])
	{
		assetfile[assets->i] = content[assets->i];
		assets->i++;
	}
	assetfile[assets->i] = '\0';
	return (1);
}

int	is_asset(char *line, t_assets *assets)
{
	assets->i = 0;
	while (line[assets->i])
	{
		while (line[assets->i] == ' ' || line[assets->i] == 9)
			assets->i++;
		if (line[assets->i] == 'N' && line[assets->i+1] == 'O')
			return (write_to_assetfile(assets->no, &line[assets->i], assets, "NO"));
		else if (line[assets->i] == 'E' && line[assets->i+1] == 'A')
			return (write_to_assetfile(assets->ea, &line[assets->i], assets, "EA"));
		else if (line[assets->i] == 'S' && line[assets->i+1] == 'O')
			return (write_to_assetfile(assets->so, &line[assets->i], assets, "SO"));
		else if (line[assets->i] == 'W' && line[assets->i+1] == 'E')
			return (write_to_assetfile(assets->we, &line[assets->i], assets, "WE"));
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
