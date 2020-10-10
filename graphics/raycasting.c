/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 01:29:01 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/10 22:38:25 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void print_ray(t_data *img, int x, int y, double start, double len)
{
	int c = 0;

	while (c < (int)len)
	{
		my_mlx_pixel_put(img, x + c * cos(start), y - c * sin(start), 0xFF9900);
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

void	make_angle(double *ray)
{
	while (*ray > 2 * M_PI)
		*ray -= 2 * M_PI;
	while (*ray < 0)
		*ray += 2 * M_PI;
}
static double horizontal_ray(t_vars *vars, double ray)
{
	double cord_x;
	double cord_y;
	int map_x;
	int map_y;

	
	cord_y = 0;
	cord_x = 0;
    cord_y = ((int)(vars->Py / 64)) * 64 + (ft_look_up(ray) == 1 ? -0.0001 : 64); // Была ошибка
	cord_x = vars->Px + (vars->Py - cord_y) / tan(ray);
	make_angle(&ray);
	if (ray > 0 && ray < M_PI)
    {
        vars->Xa = 64 / tan(ray);           
    }
    else // ray > M_PI && ray < M_PI * 2
    {
        vars->Xa = 64 / tan(2 * M_PI - ray);
    }
	vars->Ya = (ft_look_up(ray) == 1) ? -64 : 64; // Была ошибка
	map_x = (int)(cord_x / 64);
	map_y = (int)(cord_y / 64);
	while (map_x >= 0 && map_y >= 0 && map_x < vars->len_x && map_y < vars->len_y
		&& vars->map[map_y][map_x] != '1')
    {
        cord_x += vars->Xa;
		cord_y += vars->Ya;
		map_x = ((int)(cord_x / 64));
		map_y = ((int)(cord_y / 64));
    }
	return (sqrt(pow(cord_x - vars->Px, 2) + pow(cord_y - vars->Py, 2)));
}

static double vertical_ray(t_vars *vars, double ray)
{
	double cord_x;
	double cord_y;
	int map_x;
	int map_y;
	
	cord_y = 0;
	cord_x = 0;
	cord_x = ((int)(vars->Px / 64)) * 64 + (ft_look_right(ray) == 1 ? 64 : -0.0001);
	cord_y = vars->Py  + (vars->Px - cord_x) * tan(ray);
	make_angle(&ray);
    if (ray > 3 * M_PI / 2 || ray < M_PI_2)
    {
        vars->Ya = tan(2 * M_PI - ray) * 64;   
    }
    else
    {
        vars->Ya = tan(ray) * 64;    
    }
    vars->Xa = (ft_look_right(ray) == 1) ? 64 : -64;
	map_x = (int)(cord_x / 64);
	map_y = (int)(cord_y / 64);
	while (map_x >= 0 && map_y >= 0 && map_x < vars->len_x && map_y < vars->len_y
		&& vars->map[map_y][map_x] != '1')
	{
		cord_x += vars->Xa;
		cord_y += vars->Ya;
		map_x = (int)(cord_x / 64);
		map_y = (int)(cord_y / 64);
	}
	return (sqrt(pow(cord_x - vars->Px, 2) + pow(cord_y - vars->Py, 2)));
}

int create_walls(t_vars *vars, double current_len, int num_wall)
{
	int dist_from_player;
	int wall_height;
	int top_position_of_wall;

	dist_from_player = vars->s_width / 2 / tan(M_PI / 6);
	wall_height = 64 / current_len * dist_from_player;
	wall_height = (wall_height % 2 == 0) ? wall_height : wall_height + 1;
	top_position_of_wall = abs(vars->s_height - wall_height) / 2;
	
	while (wall_height > 0)
	{
		if (top_position_of_wall >= vars->s_height)
		{
			top_position_of_wall = 0;
			wall_height = vars->s_height;
		}
		if (num_wall >= vars->s_width)
			num_wall = 0;
		my_mlx_pixel_put(&(vars->img), num_wall, top_position_of_wall, 0X808080);
		top_position_of_wall++;
		wall_height--;
		// printf("%d\n", top_position_of_wall);
	}
	return 0;
}

int				cast_ray(t_vars *vars)
{
	double      start;
	double		vert_len;
	double		horiz_len;
	double		current_len;
	int			num_wall;
	double		end;
	
	num_wall = 0;
	start = vars->POV - M_PI / 6;
	end = vars->POV + M_PI / 6;
	while (start <= end)
	{   
		current_len = 0;
		if (ft_look_up(start) == 0)
			current_len = vertical_ray(vars, start);
		else if (ft_look_right(start) == 0)
			current_len = horizontal_ray(vars, start);
		else 
		{
			vert_len = vertical_ray(vars, start);
			horiz_len = horizontal_ray(vars, start);
			vert_len = (vert_len < 0) ? horiz_len : vert_len;
			horiz_len = (horiz_len < 0) ? vert_len : horiz_len;
			current_len = vert_len > horiz_len ? horiz_len : vert_len;
		}
		// print_ray(&vars->img, vars->Px, vars->Py, start, cos(vars->POV - start) * current_len);
		create_walls(vars, cos(vars->POV - start) * current_len, num_wall);
		start += ((M_PI / 3) / screenWidth);
		num_wall++;
	}
    return (0);
}