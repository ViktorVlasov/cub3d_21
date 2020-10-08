/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 01:29:01 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/08 04:34:36 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void print_ray(t_img *img, int x, int y, double start, int len)
{
	int c = 0;

	while (c < len)
	{
		my_mlx_pixel_put(img, x + c * cos(start), y + c * sin(start), 0Xcccccc);
		c++;
	}	
}

int		ft_look_up(double f)
{
	while (f > 2 * M_PI)
		f -= 2 * M_PI;
	while (f < 0)
		f += 2 * M_PI;
	if (f > 0 && f < M_PI)
		return (1);
	if (f == 0 || f == M_PI)
		return (0);
	return (-1);
}

int		ft_look_right(double f)
{
	while (f > 2 * M_PI)
		f -= 2 * M_PI;
	while (f < 0)
		f += 2 * M_PI;
	if (f < M_PI / 2 || f > 3 * M_PI / 2)
		return (1);
	if (f == M_PI / 2 || f == 3 * M_PI / 2)
		return (0);
	return (-1);
}

static int horizontal_ray(t_vars *vars, double ray, int x_len, int y_len)
{
	double cord_x;
	double cord_y;
	int map_x;
	int map_y;

	
	cord_y = 0;
	cord_x = 0;
    cord_y = ((int)(vars->Py / 64)) * 64 + (ft_look_up(ray) == 1 ? -0.0001 : 64); // Была ошибка
	if (ray > 0 && ray < M_PI)
    {
        cord_x = vars->Px + abs(vars->Py - cord_y) / tan(ray);
        vars->Xa = vars->Ya / tan(ray);           
    }
    else // ray > M_PI && ray < M_PI * 2
    {
        cord_x = vars->Px + abs(vars->Py - cord_y) / tan(2 * M_PI - ray);
        vars->Xa = vars->Ya / tan(2 * M_PI - ray);
    }
	vars->Ya = (ft_look_up(ray) == 1) ? -64 : 64; // Была ошибка
	
	map_x = (int)(cord_x / 64);
	map_y = (int)(cord_y / 64);
	while (map_x >= 0 && map_y >= 0 && map_x < x_len && map_y < y_len
		&& vars->map[map_y][map_x] != '1')
    {
        cord_x += vars->Xa;
		cord_y += vars->Ya;
		map_x = ((int)(cord_x / 64));
		map_y = ((int)(cord_y / 64));
    }
	return (sqrt(pow(cord_x - vars->Px, 2) + pow(cord_y - vars->Py, 2)));
}

static int vertical_ray(t_vars *vars, double ray, int x_len, int y_len)
{
	double cord_x;
	double cord_y;
	int map_x;
	int map_y;
	double check;
	
	cord_y = 0;
	cord_x = 0;
	cord_x = ((int)(vars->Py / 64)) * 64 + (ft_look_right(ray) == 1 ? 64 : -0.0001);
	check = tan(ray);
	cord_y = vars->Py  + (vars->Px - cord_x)*tan(ray) * (-1); // *(-1) (возможно)
	vars->Xa = (ft_look_right(ray) == 1) ? 64 : -64;
	vars->Ya = tan(ray)*vars->Xa;

	map_x = (int)(cord_x / 64);
	map_y = (int)(cord_y / 64);
	while (map_x >= 0 && map_y >= 0 && map_x < x_len && map_y < y_len
		&& vars->map[map_y][map_x] != '1')
	{
		cord_x += vars->Xa;
		cord_y += vars->Ya;
		map_x = (int)(cord_x / 64);
		map_y = (int)(cord_y / 64);
	}
	return (sqrt(pow(cord_x - vars->Px, 2) + pow(cord_y - vars->Py, 2)));
}

int cast_ray(t_vars *vars, t_img *img, t_params *params)
{
	double      start;
	int vert_len;
	int horiz_len;
	int current_len;
	
	start = vars->POV - FOV / 2;
	current_len = 0;
	if (ft_look_up(start) == 0)
		current_len = vertical_ray(vars, start);
	else if (ft_look_right(start) == 0)
		current_len = horizontal_ray(vars, start);
	else 
	{
		vert_len = vertical_ray(vars, start);
		horiz_len = horizontal_ray(vars, start);
		current_len = vert_len > horiz_len ? horiz_len : vert_len;
	}
	print_ray(img, vars->Px, vars->Py, start, current_len);
	start += 60 / screenWidth; //поменял FOV на 60

//перевернутая по каким-то причинам ориентация N и S
//не отображается первая строчка
//сегфол вечный...
//при S - кривой луч

	
	// start = vars->POV - FOV / 2;
	// double end = vars->POV + FOV / 2;
	// while (start <= end)
	// {   
	// 	current_len = 0;
	// 	if (ft_look_up(start) == 0)
	// 		current_len = vertical_ray(vars, start, params->len_x, params->len_y);
	// 	else if (ft_look_right(start) == 0)
	// 		current_len = horizontal_ray(vars, start, params->len_x, params->len_y);
	// 	else 
	// 	{
	// 		vert_len = vertical_ray(vars, start, params->len_x, params->len_y);
	// 		horiz_len = horizontal_ray(vars, start, params->len_x, params->len_y);
	// 		current_len = vert_len > horiz_len ? horiz_len : vert_len;
	// 	}
	// 	print_ray(img, vars->Px, vars->Py, start, current_len);
	// 	start += (60.0 / screenWidth);
	// 	// start += 0.005;
	// }
	// return (0);
}