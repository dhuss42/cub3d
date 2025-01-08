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

#ifndef CUB_TYPEDEF_H
# define CUB_TYPEDEF_H

# include <stdint.h>

typedef enum e_custom_error
{
	E_ARGS = 107,
	E_EMPTYFILE,
	E_DUPLICATE,
	E_LINECONTENT,
	E_INVALIDNBR
}				t_custom_error;

typedef struct s_assets
{
	char			*no;	//filename to NO asset
	char			*ea;
	char			*so;
	char			*we;
	uint32_t		c;		//color ceiling
	uint32_t		f;		//color floor
	int				err;
	int				i;
}					t_assets;

/*
	---- how to transform uint32_t (little endian) into single colors ----
	uint8_t red = (nbr_uint32 >> 16) & 0xFF;
	uint8_t green = (nbr_uint32 >> 8) & 0xFF;
	uint8_t blue = nbr_uint32 & 0xFF;
*/

typedef struct s_map
{
	char	**map;
	bool	is_map;
	int		line_counter;
	int		line_start_map;
	int		j;
}					t_map;


typedef struct s_cub
{
	t_map		*mapy;
	t_assets	*assets;
}					t_cub;

# endif
