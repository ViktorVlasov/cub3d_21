/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 11:08:34 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/03 18:38:56 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		parse_resolution(t_params *params, char **parsed_line,
unsigned char *flags)
{
	int i;

	*flags = *flags | FLG_RES;
	if (get_amount_line(parsed_line) != 3)
		return (-1);
	i = 0;
	while (parsed_line[1][i])
		if (!ft_isdigit(parsed_line[1][i++]))
			return (-1);
	i = 0;
	while (parsed_line[2][i])
		if (!ft_isdigit(parsed_line[2][i++]))
			return (-1);
	params->resolution[0] = ft_atoi(parsed_line[1]);
	params->resolution[1] = ft_atoi(parsed_line[2]);
	return (0);
}
