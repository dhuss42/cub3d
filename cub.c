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

	void	leaks(void)
	{
		system("leaks ./cub3D");
	}

	int	main(int argc, char **argv)
{
	// atexit(leaks);
	t_cub cub;
	if (argc != 2)
		print_error_free_exit(E_ARGS, NULL, NULL);
	parser(argv[1], &cub);
	free_cub(&cub);
	// char *str = malloc(1000);
	// (void)str;
	// leaks();
	// exit (0);
	return (0);
}
