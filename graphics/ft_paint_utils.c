/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 20:20:11 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/17 20:25:06 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void paint_ceiling(t_vars *vars, int top_pos_of_wall, int num_wall)
{
	int y;

	y = 0;
	while (y < top_pos_of_wall)
	{
		my_mlx_pixel_put(&(vars->img), num_wall, y, vars->ceilling_color);
		y++;
	}
}

void paint_floor(t_vars *vars, int bot_pos_of_wall, int num_wall)
{
	while (bot_pos_of_wall < vars->s_height)
	{
		my_mlx_pixel_put(&(vars->img), num_wall, bot_pos_of_wall, vars->floor_color);
		bot_pos_of_wall++;
	}
}

void get_hor_texture(t_vars *vars, t_data *current_texture)
{
	if (vars->current_ray > 0 && vars->current_ray < M_PI)
		*current_texture = vars->textur.n_img;
	else if (vars->current_ray > M_PI && vars->current_ray < 2 * M_PI)
		*current_texture = vars->textur.s_img;
}

void get_vert_texture(t_vars *vars, t_data *current_texture)
{
	if (vars->current_ray > 3 * M_PI / 2 || vars->current_ray < M_PI_2)
		*current_texture = vars->textur.e_img;
	else if (vars->current_ray > M_PI_2 && vars->current_ray < 3 * M_PI / 2)
		*current_texture = vars->textur.w_img;
}
