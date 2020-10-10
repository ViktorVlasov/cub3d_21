/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 19:47:35 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/10 22:30:47 by efumiko          ###   ########.fr       */
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

int			ft_error(int flag)
{
	if (flag == 1)
		perror("Error file");
	if (flag == 2)
		perror("Error amount arguments");
	if (flag == 3)
		perror("Error second arguments");
	if (flag == 4)
		perror("Error allocate memory");
	if (flag == 5)
		perror("Error uncorrect strings in file");
	if (flag == 6)
		perror("Error map format");
	return (0);
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
		return (argc > 3 ? ft_error(2) : ft_error(3));
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		screen = 1;
	if (!(params = ft_init_param()))
		return (ft_error(4));
	if (!(textures = ft_init()))
		return (ft_error(4));
	if (parser(params, textures, fd))
		return (ft_error(5));
	if (!(params->map = get_map(fd, params)))
		return (ft_error(6));
	close(fd);
	start(params, textures, screen);
}
