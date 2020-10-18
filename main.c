/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 21:19:34 by ddraco            #+#    #+#             */
/*   Updated: 2020/10/18 23:27:35 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_txtr		*ft_init(void)
{
	t_txtr	*textures;

	if (!(textures = malloc(sizeof(t_txtr))))
		return (NULL);
	textures->no_texture = NULL;
	textures->so_texture = NULL;
	textures->we_texture = NULL;
	textures->ea_texture = NULL;
	textures->sprite_texture = NULL;
	return (textures);
}

t_params	*ft_init_param(void)
{
	t_params *params;

	if (!(params = malloc(sizeof(t_params))))
		return (NULL);
	params->len_x = 0;
	params->len_y = 0;
	params->resolution[0] = 0;
	params->resolution[1] = 0;
	params->floor_color = 0;
	params->ceilling_color = 0;
	return (params);
}

int			ft_check_dotcub(char *path)
{
	int len;

	len = ft_strlen(path) - 1;
	if (len > 3)
		if (path[len - 3] == '.' && path[len - 2] == 'c' && \
			path[len - 1] == 'u' && path[len] == 'b')
			return (0);
	return (1);
}

void		ft_error(int flag)
{
	if (flag == 1)
		ft_putstr_fd("Error\nError file", 1);
	if (flag == 2)
		ft_putstr_fd("Error\nError amount arguments", 1);
	if (flag == 3)
		ft_putstr_fd("Error\nError second arguments", 1);
	if (flag == 4)
		ft_putstr_fd("Error\nError allocate memory", 1);
	if (flag == 5)
		ft_putstr_fd("Error\nError uncorrect strings in file", 1);
	if (flag == 6)
		ft_putstr_fd("Error\nError map format", 1);
	if (flag == 7)
		ft_putstr_fd("Error\nBad textures", 1);
	exit(0);
}

int			main(int argc, char **argv)
{
	int			screen;
	int			fd;
	t_txtr		*textures;
	t_params	*params;

	if (argc == 1 || ft_check_dotcub(argv[1])
	|| ((fd = open(argv[1], O_RDONLY)) < 0))
		ft_error(1);
	if (argc > 3 || (argc == 3 && ft_strcmp(argv[2], "--save") != 0))
		argc > 3 ? ft_error(2) : ft_error(3);
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		screen = 1;
	if (!(params = ft_init_param()))
		ft_error(4);
	if (!(textures = ft_init()))
		ft_error(4);
	if (parser(params, textures, fd))
		ft_error(5);
	if (!(params->map = get_map(fd, params)))
		ft_error(6);
	close(fd);
	start(params, textures, screen);
}
