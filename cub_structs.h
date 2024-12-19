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

# include <stdint.h>

typedef enum e_custom_error
{
	E_ARGS = 107,
	E_EMPTYFILE,
	E_DUPLICATE
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
	// int			*c_int;	//before transformation to uint32_t
	// int			*f_int;	//maybe not necessary
}					t_assets;

typedef struct s_cub
{
	char		**map;
	t_assets	*assets;
}					t_cub;

# endif
