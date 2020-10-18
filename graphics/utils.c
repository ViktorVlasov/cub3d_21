/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:25:05 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/19 00:03:57 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		check_textur_correct(t_vars *vars)
{
	if (!(vars->textur.n_img.img) || !(vars->textur.s_img.img) || !(vars->\
		textur.w_img.img) || !(vars->textur.e_img.img))
		ft_error(7);
}

void		free_textures(t_txtr *textures)
{
	if (textures != NULL)
	{
		if (textures->ea_texture)
			free(textures->ea_texture);
		if (textures->no_texture)
			free(textures->no_texture);
		if (textures->so_texture)
			free(textures->so_texture);
		if (textures->we_texture)
			free(textures->we_texture);
		if (textures->sprite_texture)
			free(textures->sprite_texture);
		free(textures);
	}
}
