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
# include "MLX42/include/MLX42/MLX42.h"
// MLX42/build/libmlx42.a -lglfw -framework Cocoa -framework OpenGL -framework IOKit
// -> needed for compilation with MLX


# include <stdio.h>
# include <errno.h>

//---------------- COLORS --------------//
# define RESET       "\033[0m"
# define BLACK       "\033[30m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

/*---------------- ERRORS ----------------*/
int	print_error(t_custom_error err);

/*---------------- PARSER -----------------*/
void	parser(char *cub_file, t_cub *cub);

# endif
