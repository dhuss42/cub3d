/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:54:45 by dhuss             #+#    #+#             */
/*   Updated: 2025/02/11 10:14:11 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	raycaster(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->width)
	{
		rays(game, x);
		distance_to_first_side(game);
		dda(game);
		plane_to_wall_distance(game);
		calculate_line_height(game);
		exact_hit_point(game);
		scale_to_texture_width(game);
		loop_y_axis(game, x);
		x++;
	}
}
