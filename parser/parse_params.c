/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:34:53 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/12 18:02:55 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_create_color(int red, int green, int blue)
{
	if (red <= 255 && red >= 0 && \
		green <= 255 && green >= 0 && \
		blue <= 255 && blue >= 0)
		return (red << 16 | green << 8 | blue);
	return (-1);
}
//r << 16 | g << 8 | b

int		ft_valid_numbers(char **colors)
{
	int i;
	int k;

	i = 0;
	while (colors[i])
	{
		k = 0;
		while (colors[i][k])
		{
			if (!ft_isdigit(colors[i][k]) || ft_strlen(colors[i]) > 3)
				return (-1);
			k++;
		}
		i++;
	}
	return (0);
}

int		parse_params(t_params *params, char **parsed_line, unsigned char *flags)
{
	char **colors;

	if (get_amount_line(parsed_line) != 2)
		return (-1);
	colors = ft_split(parsed_line[1], ',');
	if (ft_valid_numbers(colors) == -1)
	{
		ft_free_array(&colors);
		return (-1);
	}
	if (!ft_strcmp(parsed_line[0], "F")
	&& (*flags = *flags | FLG_FLOOR))
		params->floor_color = ft_create_color(ft_atoi(colors[0]),
		ft_atoi(colors[1]), ft_atoi(colors[2]));
	else if (!ft_strcmp(parsed_line[0], "C")
	&& (*flags = *flags | FLG_CEIL))
		params->ceilling_color = ft_create_color(ft_atoi(colors[0]),
				ft_atoi(colors[1]), ft_atoi(colors[2]));
	ft_free_array(&colors);
	return (0);
}
