/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:37:08 by maustel           #+#    #+#             */
/*   Updated: 2024/12/18 16:37:08 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "cub_structs.h"
# include "./libft/libft.h"

# include <stdio.h>

/*------------- ERRORS ---------------------*/
int	print_error(t_custom_error err);

/*------------- PARSER ---------------------*/
void	parser(char *cub_file, t_cub *cub);

# endif
