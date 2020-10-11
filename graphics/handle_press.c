/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 00:27:54 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/10 23:30:14 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win_mlx);
	exit(0);
}

int events(int keycode, t_vars *vars)
{
	int change_x;
	int change_y;
	
	change_x = 20 * cos(vars->POV);
	change_y = 20 * sin(vars->POV);
	if (keycode == 53)
		ft_close(vars);
	if (keycode == 13)
	{
		if (vars->map[(int)((vars->Py - change_y) / 64)][(int)((vars->Px + change_x) / 64)] != '1')
		{
			vars->Px += change_x;
			vars->Py -= change_y;
		}
	}
	if (keycode == 1)
	{
		if (vars->map[(int)((vars->Py + change_y) / 64)][(int)((vars->Px - change_x) / 64)] != '1')
		{
			vars->Px -= change_x;
			vars->Py += change_y;
		}
	}
	if (keycode == 2)
	{
		if (vars->map[(int)((vars->Py + change_y) / 64)][(int)((vars->Px - change_x) / 64)] != '1')
		{
			vars->Px -= 5 * cos(M_PI_2 - vars->POV);
			vars->Py -= 5 * sin(M_PI_2 - vars->POV);
		}
	}
	if (keycode == 0)
	{
		if (vars->map[(int)((vars->Py + change_y) / 64)][(int)((vars->Px - change_x) / 64)] != '1')
		{
			vars->Px += 5 * cos(M_PI_2 - vars->POV);
			vars->Py += 5 * sin(M_PI_2 - vars->POV);
		}
	}
    if (keycode == 124)
	{
        printf("%f\n", vars->POV); 
		vars->POV += 0.0872665;
		if (vars->POV <= 0)
			vars->POV += 2 * M_PI;
	}
	if (keycode == 123)
	{
        printf("%f\n", vars->POV); 
		vars->POV -= 0.0872665;
		if (vars->POV >= 2 * M_PI)
			vars->POV -= 2 * M_PI;	
	}
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, vars->s_width, vars->s_height);
    vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	// t_draw_map(&vars->img, vars->map);
    // my_mlx_pixel_put(&(vars->img), vars->Px, vars->Py, GREEN); 
    cast_ray(vars);
    mlx_put_image_to_window(vars->mlx, vars->win_mlx, vars->img.img, 0, 0);		
    return (0);
}