/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 09:52:08 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/18 23:13:49 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		managed_parse(t_params *params, t_txtr *textures, char **parsed_line,
					unsigned char *flags)
{
	if (ft_strcmp(parsed_line[0], "R") == 0 && (*flags & FLG_RES) == 0)
		return (parse_resolution(params, parsed_line, flags));
	if (ft_strcmp(parsed_line[0], "F") == 0 && (*flags & FLG_FLOOR) == 0)
		return (parse_params(params, parsed_line, flags));
	if (ft_strcmp(parsed_line[0], "C") == 0 && (*flags & FLG_CEIL) == 0)
		return (parse_params(params, parsed_line, flags));
	if (ft_strcmp(parsed_line[0], "NO") == 0 && (*flags & FLG_NORTH) == 0)
		return (parse_textures(textures, parsed_line, flags));
	if (ft_strcmp(parsed_line[0], "SO") == 0 && (*flags & FLG_SOUTH) == 0)
		return (parse_textures(textures, parsed_line, flags));
	if (ft_strcmp(parsed_line[0], "WE") == 0 && (*flags & FLG_WEST) == 0)
		return (parse_textures(textures, parsed_line, flags));
	if (ft_strcmp(parsed_line[0], "EA") == 0 && (*flags & FLG_EAST) == 0)
		return (parse_textures(textures, parsed_line, flags));
	if (ft_strcmp(parsed_line[0], "S") == 0 && (*flags & FLG_SPR) == 0)
		return (parse_textures(textures, parsed_line, flags));
	return (-1);
}

void	ft_free_txt(t_txtr *texture)
{
	free(texture->no_texture);
	free(texture->so_texture);
	free(texture->we_texture);
	free(texture->ea_texture);
	free(texture->sprite_texture);
	free(texture);
}

int		ft_free_parse(t_params *param, t_txtr *txt, char **pars, char *line)
{
	free(line);
	ft_free_array(&pars);
	ft_free_txt(txt);
	free(param);
	return (-1);
}

int		parser(t_params *params, t_txtr *textures, int fd)
{
	char			*line;
	unsigned char	flags;
	char			**parsed_line;
	int				check;

	flags = FLG_NONE;
	while (flags != 255 && (check = get_next_line(fd, &line)))
	{
		parsed_line = ft_split(line, ' ');
		if (line[0] != '\0')
			if (managed_parse(params, textures, parsed_line, &flags) == -1)
				return (ft_free_parse(params, textures, parsed_line, line));
		free(line);
		ft_free_array(&parsed_line);
		check = 0;
	}
	return (0);
}
