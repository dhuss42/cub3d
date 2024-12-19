/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:13:51 by maustel           #+#    #+#             */
/*   Updated: 2024/12/19 11:13:51 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	parser(char *cub_file, t_cub *cub)
{
	int		fd;

	fd = open(cub_file, O_RDONLY);
	printf( "fd: %d\n", fd);
	if (fd < 0)
		exit (print_error(errno));

	(void)cub;
	(void)cub_file;
}
