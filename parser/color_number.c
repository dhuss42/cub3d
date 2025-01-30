/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 09:53:28 by maustel           #+#    #+#             */
/*   Updated: 2025/01/08 09:53:28 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*------------------------------------------------------------------------
Skip all whitespaces, then read number until ',' or newline or whitespace
(example: F 66, 110, 65)
Number will be written into string
Function returns int number
------------------------------------------------------------------------*/
static int	get_single_number(t_assets *assets, char *line)
{
	char	nbr_str[4];
	int		j;

	j = 0;
	while (line[assets->i] == ' ' || line[assets->i] == '+')
		assets->i++;
	while (line[assets->i] && line[assets->i] != ','
		&& line[assets->i] != ' ' && line[assets->i] != '\n')
	{
		while (j == 0 && line[assets->i] == '0'
			&& ft_isdigit(line[assets->i + 1]))
			assets->i++;
		if (!assets->err && (!ft_isdigit (line[assets->i]) || j > 2))
		{
			print_error(E_INVALIDNBR, &assets->err, line);
			return (-1);
		}
		nbr_str[j] = line[assets->i];
		assets->i++;
		j++;
	}
	nbr_str[j] = '\0';
	if (!assets->err && (j == 0 || ft_atoi(nbr_str) > 255))
		print_error(E_INVALIDNBR, &assets->err, line);
	return (ft_atoi(nbr_str));
}

static void	skip_ws_until_comma(t_assets *assets, char *line)
{
	while (line[assets->i] == ' ')
		assets->i++;
	if (line[assets->i] == ',')
		assets->i++;
	else
		print_error(E_INVALIDNBR, &assets->err, line);
}

/*------------------------------------------------------------------------
convert int array into uint32
little endian ( = less significant byte first)
--- how to transform uint32_t (little endian) into single colors ---
	uint8_t red = (nbr_uint32 >> 16 & 0xFF); ->takes the 8 bits on the left
	uint8_t green = (nbr_uint32 >> 8 & 0xFF);
	uint8_t blue = nbr_uint32 & 0xFF; -->takes the 8 bits on the right
nbr_uint32:	10001110 10111111 10010011
			red			green	blue
------------------------------------------------------------------------*/
uint32_t	int_to_uint32(int *nbr_int)
{
	uint32_t	nbr_uint32;

	nbr_uint32 = 0;
	nbr_uint32 |= (uint32_t)nbr_int[0] << 16;
	nbr_uint32 |= (uint32_t)nbr_int[1] << 8;
	nbr_uint32 |= (uint32_t)nbr_int[2];
	return (nbr_uint32);
}

/*------------------------------------------------------------------------
Write the three colors as int into int array
then return them as uint32_t
------------------------------------------------------------------------*/
uint32_t	color_to_uint32(t_assets *assets, char *line)
{
	int		nbr_int[3];
	int		n;

	assets->i++;
	while (line[assets->i] == ' ' || line[assets->i] == 9)
		assets->i++;
	n = 0;
	while (n < 3)
	{
		nbr_int[n] = get_single_number(assets, line);
		if (nbr_int[n] < 0)
			return (16777216);
		if (n < 2 && !assets->err)
			skip_ws_until_comma(assets, line);
		else if (n >= 2 && !assets->err)
			check_rest_line(assets, line);
		n++;
	}
	if (!assets->err)
		return (int_to_uint32(nbr_int));
	return (16777216);
}
