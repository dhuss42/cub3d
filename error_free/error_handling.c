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

int	custom_error_3(t_custom_error err)
{
	if (err == E_MLXINIT)
		ft_putstr_fd("Mlx_init failed!\n", 2);
	else if (err == E_MLXIMG)
		ft_putstr_fd("Mlx_new_img failed!\n", 2);
	else if (err == E_MLXIMGTOWIN)
		ft_putstr_fd("Mlx_img_to_window failed!\n", 2);
	else if (err == E_MLXLOADPNG)
		ft_putstr_fd("Mlx_load_png failed!\n", 2);
	return (err);
}

int	custom_error_2(t_custom_error err, char *str)
{
	if (err == E_MALLOC)
		ft_putstr_fd("Malloc failed!\n", 2);
	else if (err == E_MISSING)
	{
		ft_putstr_fd("Missing part in input file: ", 2);
		ft_putstr_fd(str, 2);
	}
	else if (err == E_FILENAME)
		ft_putstr_fd("Input filename not ending on '.cub'!\n", 2);
	else if (err == E_NOMAP)
		ft_putstr_fd("No map or map in wrong position!\n", 2);
	else if (err == E_NEWLINEMAP)
		ft_putstr_fd("Newline in map!\n", 2);
	else if (err == E_TOOMANYPLAYERS)
		ft_putstr_fd("Too many players!\n", 2);
	else if (err == E_NOPLAYER)
		ft_putstr_fd("No player!\n", 2);
	else if (err == E_OPENMAP)
		ft_putstr_fd("Map is not surrounded by walls!\n", 2);
	else
		return (custom_error_3(err));
	return (err);
}

int	custom_error(t_custom_error err, char *str)
{
	if (err == E_ARGS)
		ft_putstr_fd("Wrong amount of arguments!\n", 2);
	else if (err == E_EMPTYFILE)
		ft_putstr_fd("Empty file!\n", 2);
	else if (err == E_DUPLICATE)
	{
		ft_putstr_fd("Duplicate: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (err == E_LINECONTENT)
	{
		ft_putstr_fd("Invalid content in line: ", 2);
		ft_putstr_fd(str, 2);
	}
	else if (err == E_INVALIDNBR)
	{
		ft_putstr_fd("Invalid content in line: ", 2);
		ft_putstr_fd(str, 2);
	}
	else
		return (custom_error_2(err, str));
	return (err);
}

void	print_error_free_exit(t_custom_error err, t_cub *cub, char *str)
{
	ft_putstr_fd(RED"Error!\n", 2);
	if (err > 106)
		custom_error(err, str);
	else if (err <= 106)
	{
		if (str)
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\n", 2);
		}
		perror(NULL);
		err = errno;
	}
	if (cub)
		free_cub(cub);
	exit (err);
}

void	print_error(t_custom_error err, int *err_msg, char *str)
{
	*err_msg = err;
	ft_putstr_fd(RED"Error!\n", 2);
	if (err > 106)
		custom_error(err, str);
	else if (err <= 106)
		perror(NULL);
}
