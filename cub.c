/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:38:12 by maustel           #+#    #+#             */
/*   Updated: 2024/12/18 16:38:12 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_cub cub;
	if (argc != 2)
		print_error_free_exit(E_ARGS, NULL, NULL);
	parser(argv[1], &cub);
	free_cub(&cub);
	(void)argv;
	return (0);
}
