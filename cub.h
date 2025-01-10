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

# include "cub_typedef.h"
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

/*---------------- ERROR_FREE ----------------*/
void	print_error_free_exit(t_custom_error err, t_cub *cub, char *str);
void	print_error(t_custom_error err, char *str);
void	free_cub(t_cub *cub);
void	free_exit(int err, t_cub *cub);

/*---------------- PARSER -----------------*/
void	parser(char *cub_file, t_cub *cub);
int		is_asset(char *line, t_assets *assets);
int		is_color(char *line, t_assets *assets);
int		is_map(char *line, t_cub *cub);
void	check_rest_line(t_assets *assets, char *line);
uint32_t		color_to_uint32(t_assets *assets, char *line);
void	get_map(char *cub_file, t_cub *cub);
void	check_content(t_cub *cub);

# endif
