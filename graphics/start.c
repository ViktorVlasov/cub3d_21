/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 23:35:22 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/19 11:23:15 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	void	init_vars(t_vars *vars, t_params *params)
{
	int max_width;
	int max_height;

	vars->mlx = mlx_init();
	mlx_get_screen_size(vars->mlx, &max_width, &max_height);
	vars->s_width = params->resolution[0] >= max_width \
	? max_width : params->resolution[0];
	vars->s_height = params->resolution[1] >= max_height \
	? max_height : params->resolution[1];
	vars->len_x = params->len_x;
	vars->len_y = params->len_y;
	vars->ceilling_color = params->ceilling_color;
	vars->floor_color = params->floor_color;
	vars->map = params->map;
	vars->offset_y_vert = -1;
	vars->offset_x_hor = -1;
	vars->win_mlx = mlx_new_window(vars->mlx, vars->s_width, \
		vars->s_height, "Cub3D");
	vars->img.img = mlx_new_image(vars->mlx, vars->s_width, vars->s_height);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
	&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
}

static	void	init_mlx_texture(t_vars *vars, t_txtr *textures)
{
	vars->textur.n_img.img = mlx_xpm_file_to_image(vars->mlx, textures->\
	no_texture, &vars->textur.n_img.img_width, &vars->textur.n_img.img_height);
	vars->textur.s_img.img = mlx_xpm_file_to_image(vars->mlx, \
	textures->so_texture, &vars->textur.s_img.img_width, \
	&vars->textur.s_img.img_height);
	vars->textur.w_img.img = mlx_xpm_file_to_image(vars->mlx, \
	textures->we_texture, &vars->textur.w_img.img_width, \
	&vars->textur.w_img.img_height);
	vars->textur.e_img.img = mlx_xpm_file_to_image(vars->mlx, \
	textures->ea_texture, &vars->textur.e_img.img_width,\
	&vars->textur.e_img.img_height);
	check_textur_correct(vars);
	vars->textur.n_img.addr = mlx_get_data_addr(vars->textur.n_img.img,\
	&vars->textur.n_img.bits_per_pixel, \
	&vars->textur.n_img.line_length, &vars->textur.n_img.endian);
	vars->textur.s_img.addr = mlx_get_data_addr(vars->textur.s_img.img,\
	&vars->textur.s_img.bits_per_pixel, \
	&vars->textur.s_img.line_length, &vars->textur.s_img.endian);
	vars->textur.w_img.addr = mlx_get_data_addr(vars->textur.w_img.img,\
	&vars->textur.w_img.bits_per_pixel, \
	&vars->textur.w_img.line_length, &vars->textur.w_img.endian);
	vars->textur.e_img.addr = mlx_get_data_addr(vars->textur.e_img.img, \
	&vars->textur.e_img.bits_per_pixel, \
	&vars->textur.e_img.line_length, &vars->textur.e_img.endian);
}

void			init_sprites(t_vars *vars, t_txtr *textures)
{
	int i;

	i = 0;
	if (!(vars->sprites = malloc(sizeof(t_sprite) * vars->sprites_amount)))
		ft_error(4);
	while (i < vars->sprites_amount)
	{
		if (!(vars->sprites[i].img_sprite.img = mlx_xpm_file_to_image(vars->mlx,
			textures->sprite_texture, &vars->sprites[i].img_sprite.img_width,
				&vars->sprites[i].img_sprite.img_height)))
			ft_error(7);
		vars->sprites[i].img_sprite.addr = \
			mlx_get_data_addr(vars->sprites[i].img_sprite.img, \
			&vars->sprites[i].img_sprite.bits_per_pixel, \
			&vars->sprites[i].img_sprite.line_length, \
			&vars->sprites[i].img_sprite.endian);
		i++;
	}
}

void			sort_sprites(t_vars *vars)
{
	int		i;
	int		j;
	double	key_dist;
	double	key_x;
	double	key_y;

	i = 0;
	if (vars->sprites_amount > 2)
		while (i++ < vars->sprites_amount)
		{
			key_dist = vars->sprites[i].sprite_dist;
			key_x = vars->sprites[i].sprite_x;
			key_y = vars->sprites[i].sprite_y;
			j = i - 1;
			while (j >= 0 && vars->sprites[j].sprite_dist < key_dist)
			{
				vars->sprites[j + 1].sprite_x = vars->sprites[j].sprite_x;
				vars->sprites[j + 1].sprite_y = vars->sprites[j].sprite_y;
				vars->sprites[j + 1].sprite_dist = vars->sprites[j].sprite_dist;
				j--;
			}
			vars->sprites[j + 1].sprite_dist = key_dist;
			vars->sprites[j + 1].sprite_x = key_x;
			vars->sprites[j + 1].sprite_y = key_y;
		}
}

int				start(t_params *params, t_txtr *textures, int screen)
{
	t_vars		vars;
	int			i;

	init_vars(&vars, params);
	init_mlx_texture(&vars, textures);
	get_coordinates(&vars);
	ft_count_sprites(&vars);
	init_sprites(&vars, textures);
	free_textures(textures);
	get_sprite_cord(&vars);
	cast_ray(&vars);
	sort_sprites(&vars);
	i = -1;
	while (++i < vars.sprites_amount)
		get_sprite(&vars, i);
	if (vars.ray_length)
		free(vars.ray_length);
	mlx_put_image_to_window(vars.mlx, vars.win_mlx, vars.img.img, 0, 0);
	if (screen == 1)
		create_bmp(&vars);
	mlx_hook(vars.win_mlx, 17, 0, ft_close, &vars);
	mlx_hook(vars.win_mlx, 2, 0L, events, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
