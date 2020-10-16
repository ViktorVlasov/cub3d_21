/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 00:27:54 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/16 20:40:45 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			ft_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win_mlx);
	exit(0);
}

static void	ft_ws_key(int keycode, t_vars *vars)
{
	double change_x;
	double change_y;

	change_x = 10 * cos(vars->POV);
	change_y = 10 * sin(vars->POV);
	if (keycode == W_KEY)
		if (vars->map[(int)((vars->Py - change_y) / 64)][(int)((vars->Px + change_x) / 64)] != '1' &&
			vars->map[(int)((vars->Py - change_y) / 64)][(int)(vars->Px / 64)] != '1' && 
			vars->map[(int)(vars->Py / 64)][(int)((vars->Px + change_x) / 64)] != '1')
		{
			vars->Px += (int)change_x;
			vars->Py -= (int)change_y;
		}
	if (keycode == S_KEY)
		if (vars->map[(int)((vars->Py + change_y) / 64)][(int)((vars->Px - change_x) / 64)] != '1' &&
			vars->map[(int)((vars->Py + change_y) / 64)][(int)(vars->Px / 64)] != '1' && 
			vars->map[(int)(vars->Py / 64)][(int)((vars->Px - change_x) / 64)] != '1')
		{
			vars->Px -= (int)change_x;
			vars->Py += (int)change_y;
		}
}

static void	ft_ad_key(int keycode, t_vars *vars)
{
	double change_x;
	double change_y;

	change_x = 10 * cos(M_PI_2 - vars->POV);
	change_y = 10 * sin(M_PI_2 - vars->POV);
	if (keycode == A_KEY)
		if (vars->map[(int)((vars->Py - change_y) / 64)][(int)((vars->Px - change_x) / 64)] != '1' &&
			vars->map[(int)((vars->Py - change_y) / 64)][(int)(vars->Px / 64)] != '1' && 
			vars->map[(int)(vars->Py / 64)][(int)((vars->Px - change_x) / 64)] != '1')
		{
			vars->Px -= (int)change_x;
			vars->Py -= (int)change_y;
		}
	if (keycode == D_KEY)
		if (vars->map[(int)((vars->Py + change_y) / 64)][(int)((vars->Px + change_x) / 64)] != '1' &&
			vars->map[(int)((vars->Py + change_y) / 64)][(int)(vars->Px / 64)] != '1' && 
			vars->map[(int)(vars->Py / 64)][(int)((vars->Px + change_x) / 64)] != '1')
		{
			vars->Px += (int)change_x;
			vars->Py += (int)change_y;
		}
}

static void	ft_left_right(int keycode, t_vars *vars)
{
	if (keycode == LEFT_KEY)
	{
		printf("%f\n", vars->POV); 
		vars->POV += 0.0872665;
		if (vars->POV <= 0)
			vars->POV += 2 * M_PI;
	}
	if (keycode == RIGHT_KEY)
	{
		printf("%f\n", vars->POV); 
		vars->POV -= 0.0872665;
		if (vars->POV >= 2 * M_PI)
			vars->POV -= 2 * M_PI;	
	}
}

int			events(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
		ft_close(vars);
	if (keycode == W_KEY || keycode == S_KEY)
		ft_ws_key(keycode, vars);
	if (keycode == A_KEY || keycode == D_KEY)
		ft_ad_key(keycode, vars);
	if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		ft_left_right(keycode, vars);
	
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, vars->s_width, vars->s_height);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	// t_draw_map(&vars->img, vars->map);
	// my_mlx_pixel_put(&(vars->img), vars->Px, vars->Py, GREEN); 
	cast_ray(vars);


	// Отредачить
	int i = -1;
	while (++i < vars->sprites_amount)
		print_sprite(vars, i);
	
	
	mlx_put_image_to_window(vars->mlx, vars->win_mlx, vars->img.img, 0, 0);		
	return (0);
}

