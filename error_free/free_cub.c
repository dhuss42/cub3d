/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:27:30 by maustel           #+#    #+#             */
/*   Updated: 2024/12/19 16:27:30 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_double(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free (to_free[i]);
		to_free[i] = NULL;
		i++;
	}
	if (to_free)
		free (to_free);
	to_free = NULL;
}

void	free_mapy(t_map *mapy)
{
	if (mapy->map)
		free_double (mapy->map);
	if (mapy)
		free (mapy);
}

void	free_assets(t_assets *assets)
{
	if (assets->no)
		free (assets->no);
	if (assets->ea)
		free (assets->ea);
	if (assets->so)
		free (assets->so);
	if (assets->we)
		free (assets->we);
	if (assets)
		free (assets);
}

void	free_cub(t_cub *cub)
{
	if (cub->assets)
		free_assets(cub->assets);
	if (cub->mapy)
		free_mapy(cub->mapy);
}

void	free_exit(int err, t_cub *cub)
{
	free_cub(cub);
	exit (err);
}
