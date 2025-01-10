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

/*
	check if everything present (NO, WE, SO, EA, F, C , map)
*/
void	check_all_there(t_cub *cub)
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
	if (cub->assets->f > 16777215)
		print_error_free_exit(E_MISSING, cub, "'F' floor color\n");
}

void	check_content(t_cub *cub)
{
	check_all_there(cub);
	// check_filepaths_valid(cub->assets);	//todo
	// check_map(cub->mapy->map);	//todo
}
