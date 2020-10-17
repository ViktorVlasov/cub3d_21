/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_working.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 20:27:45 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/17 21:25:38 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				get_len_ray(t_vars *vars, double ray)
{
	double		vert_len;
	double		horiz_len;
	double		current_len;

	current_len = 0;
	if (ft_look_up(ray) == 0)
		current_len = vertical_ray(vars, ray);
	else if (ft_look_right(ray) == 0)
		current_len = horizontal_ray(vars, ray);
	else
	{
		vert_len = vertical_ray(vars, ray);
		horiz_len = horizontal_ray(vars, ray);
		vert_len = (vert_len < 0) ? horiz_len : vert_len;
		horiz_len = (horiz_len < 0) ? vert_len : horiz_len;
		current_len = vert_len > horiz_len ? horiz_len : vert_len;
		if (current_len == vert_len)
			vars->offset_x_hor = -1;
		else
			vars->offset_y_vert = -1;
	}
	return (current_len);
}

double			horizontal_ray(t_vars *vars, double ray)
{
	double		cord_x;
	double		cord_y;
	int			map_x;
	int			map_y;

	cord_y = (vars->py / 64) * 64 + (ft_look_up(ray) == 1 ? -0.0001 : 64);
	cord_x = vars->px + (vars->py - cord_y) / tan(ray);
	ray = make_angle(ray);
	if (ray > 0 && ray < M_PI)
		vars->xa = 64 / tan(ray);
	else
		vars->xa = 64 / tan(2 * M_PI - ray);
	vars->ya = (ft_look_up(ray) == 1) ? -64 : 64;
	map_x = (int)(cord_x / 64);
	map_y = (int)(cord_y / 64);
	while (map_x >= 0 && map_y >= 0 && map_x < vars->len_x &&\
			map_y < vars->len_y && vars->map[map_y][map_x] != '1')
	{
		cord_x += vars->xa;
		cord_y += vars->ya;
		map_x = ((int)(cord_x / 64));
		map_y = ((int)(cord_y / 64));
	}
	vars->offset_x_hor = cord_x;
	return (sqrt(pow(cord_x - vars->px, 2) + pow(cord_y - vars->py, 2)));
}

double			vertical_ray(t_vars *vars, double ray)
{
	double		cord_x;
	double		cord_y;
	int			map_x;
	int			map_y;

	cord_x = (vars->px / 64) * 64 + (ft_look_right(ray) == 1 ? 64 : -0.0001);
	cord_y = vars->py + (vars->px - cord_x) * tan(ray);
	ray = make_angle(ray);
	if (ray > 3 * M_PI / 2 || ray < M_PI_2)
		vars->ya = tan(2 * M_PI - ray) * 64;
	else
		vars->ya = tan(ray) * 64;
	vars->xa = (ft_look_right(ray) == 1) ? 64 : -64;
	map_x = (int)(cord_x / 64);
	map_y = (int)(cord_y / 64);
	while (map_x >= 0 && map_y >= 0 && map_x < vars->len_x &&\
			map_y < vars->len_y && vars->map[map_y][map_x] != '1')
	{
		cord_x += vars->xa;
		cord_y += vars->ya;
		map_x = (int)(cord_x / 64);
		map_y = (int)(cord_y / 64);
	}
	vars->offset_y_vert = cord_y;
	return (sqrt(pow(cord_x - vars->px, 2) + pow(cord_y - vars->py, 2)));
}
