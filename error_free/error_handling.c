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

int	custom_error(t_custom_error err, char *str)
{
	if (err == E_ARGS)
		ft_putstr_fd("Wrong amount of arguments!\n", 2);
	if (err == E_EMPTYFILE)
		ft_putstr_fd("Empty file!\n", 2);
	if (err == E_DUPLICATE)
	{
		ft_putstr_fd("Duplicate: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	if (err == E_LINECONTENT)
	{
		ft_putstr_fd("Unexpected content in line: ", 2);
		ft_putstr_fd(str, 2);
	}
	return (err);
}

void	print_error_free_exit(t_custom_error err, t_cub *cub, char *str)
{
	if (cub)
		free_cub(cub);
	ft_putstr_fd(RED"Error!\n", 2);
	if (err > 106)
		custom_error(err, str);
	else if (err <= 106)
	{
		perror(NULL);
		err = errno;
	}
	exit (err);
}

void	print_error(t_custom_error err, char *str)
{
	ft_putstr_fd(RED"Error!\n", 2);
	if (err > 106)
		custom_error(err, str);
	else if (err <= 106)
		perror(NULL);
}

