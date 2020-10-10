/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 12:37:45 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/03 18:39:02 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_textures(t_txtr *textures, char **parsed_line, unsigned char *flags)
{
	if (get_amount_line(parsed_line) != 2)
		return (-1);
	if (!(ft_strcmp(parsed_line[0], "NO\0")) && (*flags = *flags | FLG_NORTH))
		textures->no_texture = ft_strdup(parsed_line[1]);
	else if (!(ft_strcmp(parsed_line[0], "SO\0"))
	&& (*flags = *flags | FLG_SOUTH))
		textures->so_texture = ft_strdup(parsed_line[1]);
	else if (!(ft_strcmp(parsed_line[0], "WE\0"))
	&& (*flags = *flags | FLG_WEST))
		textures->we_texture = ft_strdup(parsed_line[1]);
	else if (!(ft_strcmp(parsed_line[0], "EA\0"))
	&& (*flags = *flags | FLG_EAST))
		textures->ea_texture = ft_strdup(parsed_line[1]);
	else if (!(ft_strcmp(parsed_line[0], "S\0"))
	&& (*flags = *flags | FLG_SPR))
		textures->sprite_texture = ft_strdup(parsed_line[1]);
	return (0);
}
