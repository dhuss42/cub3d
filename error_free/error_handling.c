/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:36:13 by maustel           #+#    #+#             */
/*   Updated: 2024/12/19 10:36:13 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	custom_error(t_custom_error err)
{
	if (err == E_ARGS)
		ft_putstr_fd(RED"Wrong amount of arguments!\n"RESET, 2);
	if (err == E_EMPTYFILE)
		ft_putstr_fd(RED"Empty file!\n"RESET, 2);
	return (err);
}

void	print_error_exit(t_custom_error err, t_cub *cub)
{
	if (cub)
		free_cub(cub);
	ft_putstr_fd(RED"Error!\n"RESET, 2);
	if (err > 106)
		custom_error(err);
	else if (err <= 106)
	{
		perror(NULL);
		err = errno;
	}
	exit (err);
}
