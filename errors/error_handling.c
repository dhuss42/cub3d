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

int	print_error(t_custom_error err)
{
	ft_putstr_fd("Error!\n", 2);
	if (err <= 106)
		perror(NULL);
	if (err == E_ARGS)
		ft_putstr_fd("Wrrong amount of arguments!\n", 2);
	return (err);
}
