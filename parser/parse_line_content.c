/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:10:36 by maustel           #+#    #+#             */
/*   Updated: 2024/12/19 17:10:36 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*------------------------------------------------------------------------
Detect unexpected content in line
------------------------------------------------------------------------*/
void	check_rest_line(t_assets *assets, char *line)
{
	while(line[assets->i] && line[assets->i] != '\n')
	{
		if (line[assets->i] != 9 && line[assets->i] != ' ')
		{
			assets->err = E_LINECONTENT;
			print_error(E_LINECONTENT, line);
			return ;
		}
		assets->i++;
	}
}

/*------------------------------------------------------------------------
Store path of NO/EA/SO/WE asset into assets->no/ea/so/we
If duplicate detected, print error, store last errornumber
and end program after finishing reading with gnl
Between NO and path: jump whitspaces and tabs
then read until whitspace or non printable character
------------------------------------------------------------------------*/
int	store_path(char **assetpath, char *line, t_assets *assets, char *as)
{
	int	tmp;

	if (*assetpath != NULL)
	{
		assets->err = E_DUPLICATE;
		print_error(E_DUPLICATE, as);
		return (1);
	}
	assets->i = assets->i + 2;
	while (line[assets->i] == ' ' || line[assets->i] == 9)
		assets->i++;
	tmp = assets->i;
	while (line[assets->i] >= 33 && 126 >= line[assets->i])
		assets->i++;
	*assetpath = ft_calloc((assets->i - tmp + 1), sizeof(char));
	if (!*assetpath)
		return (1);	//do something else (exit?)(printerror?)
	assets->i = tmp;
	while (line[assets->i] >= 33 && 126 >= line[assets->i])
	{
		assetpath[0][assets->i - tmp] = line[assets->i];
		assets->i++;
	}
	check_rest_line(assets, line);
	return (1);
}

/*------------------------------------------------------------------------
Check if in this line is stored assetpath (NO/EA/SO/WE)
in the beginning: skip all whitespaces and tabs
If yes, store it in struct
------------------------------------------------------------------------*/
int	is_asset(char *line, t_assets *assets)
{
	assets->i = 0;
	while (line[assets->i])
	{
		while (line[assets->i] == ' ' || line[assets->i] == 9)
			assets->i++;
		if (line[assets->i] == 'N' && line[assets->i + 1] == 'O')
			return (store_path(&assets->no, line, assets, "NO"));
		else if (line[assets->i] == 'E' && line[assets->i+1] == 'A')
			return (store_path(&assets->ea, line, assets, "EA"));
		else if (line[assets->i] == 'S' && line[assets->i+1] == 'O')
			return (store_path(&assets->so, line, assets, "SO"));
		else if (line[assets->i] == 'W' && line[assets->i+1] == 'E')
			return (store_path(&assets->we, line, assets, "WE"));
		assets->i++;
	}
	return (0);
}

/*------------------------------------------------------------------------
Skip all whitespaces, then read number until ',' or newline or whitespace
(example: F 66, 110, 65)
Number will be written into string
Function returns int number
------------------------------------------------------------------------*/
int	get_single_number(t_assets *assets, char *line)
{
	char	nbr_str[4];
	int		j;

	j = 0;
	while (line[assets->i] == ' ' || line[assets->i] == '+' || line[assets->i] == '0')
		assets->i++;
	while (line[assets->i] && line[assets->i] != ',' && line[assets->i] != ' ' && line[assets->i] != '\n')
	{
		if (!assets->err && (!ft_isdigit (line[assets->i]) || j > 2))
		{
			assets->err = E_INVALIDNBR;	//put this into print_error
			print_error(E_INVALIDNBR, line);
			return (-1);
		}
		nbr_str[j] = line[assets->i];
		assets->i++;
		j++;
	}
	nbr_str[j] = '\0';
	if (!assets->err && (j == 0 || ft_atoi(nbr_str) > 255))
	{
		assets->err = E_INVALIDNBR;
		print_error(E_INVALIDNBR, line);
	}
	return (ft_atoi(nbr_str));
}

void	skip_ws_until_comma(t_assets *assets, char *line)
{
	while (line[assets->i] == ' ')
		assets->i++;
	if (line[assets->i] == ',')
		assets->i++;
	else
	{
		assets->err = E_INVALIDNBR;
		print_error(E_INVALIDNBR, line);
	}
}

/*------------------------------------------------------------------------
Write the three colors as int into int array
------------------------------------------------------------------------*/
int	color_to_uint(t_assets *assets, char *line)	//change name (?)
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
			return (0);
		if (n < 2 && !assets->err)
			skip_ws_until_comma(assets, line);
		else if (n >= 2 && !assets->err)
			check_rest_line(assets, line);
		n++;
	}
	// int_to_uint32(nbr_int);	//TODO (enter only if err == 0)
	n = 0;
	while (n < 3)
	{
		printf ("%d,", nbr_int[n]);
		n++;
	}
	printf ("\n");
	return (nbr_int[n]);		//change
}


/*------------------------------------------------------------------------
Check if in this line is stored color (C/F)
in the beginning: skip all whitespaces and tabs
If yes, transform colors to uint32 and store it in struct
------------------------------------------------------------------------*/
int	is_color(char *line, t_assets *assets)
{
	assets->i = 0;
	while (line[assets->i])
	{
		while (line[assets->i] == ' ' || line[assets->i] == 9)
			assets->i++;
		if (line[assets->i] == 'C' || line[assets->i] == 'F')
		{
			// if (line[assets->i] == 'C')
			// 	assets->c = color_to_uint(assets, line);
			// else if (line[assets->i] == 'F')
			// 	assets->f = color_to_uint(assets, line);
			color_to_uint(assets, line);
			return (1);
		}
		assets->i++;
	}
	return (0);
}

int	is_map(char *line, char **map)
{
	(void)line;
	(void)map;
	return (0);
}
