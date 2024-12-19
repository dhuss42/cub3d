/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:26:59 by maustel           #+#    #+#             */
/*   Updated: 2024/12/19 10:26:59 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

typedef enum e_custom_error
{
	E_ARGS = 107
}				t_custom_error;

typedef struct s_cub
{
	char	**map;
	char	*texture_no;
	char	*texture_ea;
	char	*texture_so;
	char	*texture_we;
	char	*color_ceiling;
	char	*color_floor;
}				t_cub;

# endif
