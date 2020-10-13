/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 01:29:01 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/12 00:00:513 by ddraco           ###   ########.fr       */
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

double	make_angle(double ray)
{
	while (ray > 2 * M_PI)
		ray -= 2 * M_PI;
	while (ray < 0)
		ray += 2 * M_PI;
	return (ray);
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
	ray = make_angle(ray);
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
	vars->offset_x_hor = cord_x;
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
	ray = make_angle(ray);
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
	vars->offset_y_vert = cord_y;
	return (sqrt(pow(cord_x - vars->Px, 2) + pow(cord_y - vars->Py, 2)));
}

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

void print_sprite(t_vars *vars)
{
	double	sprite_dir;
	double	sprite_dist;
	double	sprite_size;
	int		x_offset;
	int		y_offset;
	int		h_offset;
	int		v_offset;

	sprite_dir = atan2(vars->sprites[0].sprite_y - vars->Py, vars->sprites[0].sprite_x - vars->Px);
	while (sprite_dir - vars->current_ray >  M_PI) 
		sprite_dir -= 2 * M_PI; 
    while (sprite_dir - vars->current_ray <  -M_PI)
		sprite_dir += 2 * M_PI;
	sprite_dist = sqrt(pow(vars->Px - vars->sprites[0].sprite_x, 2) + pow(vars->Py - vars->sprites[0].sprite_y, 2));
	sprite_size = ((vars->s_height / sprite_dist) > 2000) ? 2000 : vars->s_height / sprite_dist;
	
	h_offset = (sprite_dir - vars->current_ray) * vars->s_width / (FOV) + vars->s_width / 2 - sprite_size / 2;
	v_offset = vars->s_height / 2 - sprite_size / 2;
	// x_offset = (sprite_dir - vars->current_ray) * vars->s_width / (FOV) + vars->s_width / 2 - sprite_size / 2;
	// y_offset = vars->s_height / 2 - sprite_size / 2;

	for (size_t i=0; i<sprite_size; i++) {
        if (h_offset+(int)i<0 || h_offset+i>=vars->s_width)
			continue;
        for (size_t j=0; j<sprite_size; j++) {
            if (v_offset+(int)j<0 || v_offset+j>=vars->s_height)
				continue;
			my_mlx_pixel_put(&(vars->img), vars->s_width + h_offset + i, v_offset + j, GREEN);
        }
    }
}

int create_walls(t_vars *vars, double current_len, int num_wall)
{
	int dist_from_player;
	int wall_height;
	int top_position_of_wall;
	int cur_color;
	double coef;
	int y_pixel;
	int begining_of_wall;
	t_data current_texture;
	
	dist_from_player = vars->s_width / 2 / tan(M_PI / 6);
	wall_height = 64 / current_len * dist_from_player;
	wall_height = (wall_height % 2 == 0) ? wall_height : wall_height + 1;
	top_position_of_wall = ((vars->s_height - wall_height) / 2) < 0 ? 0 : (vars->s_height - wall_height) / 2;
	
	coef = 64.0 / (wall_height);
	begining_of_wall = top_position_of_wall;
	if (top_position_of_wall == 0)
	{
		begining_of_wall = (vars->s_height - wall_height) / 2;
		wall_height = vars->s_height;
	}

	paint_ceiling(vars, top_position_of_wall, num_wall);
	paint_floor(vars, top_position_of_wall + wall_height, num_wall);
	while (wall_height > 0)
	{
		y_pixel = (top_position_of_wall - begining_of_wall) * coef;
		if (vars->offset_x_hor != -1)
		{
			get_hor_texture(vars, &current_texture);
			cur_color = my_mlx_pixel_get_color(&current_texture, (int)vars->offset_x_hor % 64, y_pixel);
		}
		else
		{
			get_vert_texture(vars, &current_texture);
			cur_color = my_mlx_pixel_get_color(&current_texture, (int)vars->offset_y_vert % 64, y_pixel);
		}
		my_mlx_pixel_put(&(vars->img), num_wall, top_position_of_wall, cur_color);
		top_position_of_wall++;
		wall_height--;
	}
	print_sprite(vars);
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
	while (start <= end && num_wall < vars->s_width)
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
			current_len == vert_len ? (vars->offset_x_hor = -1) : (vars->offset_y_vert = -1);
		}
		// print_ray(&vars->img, vars->Px, vars->Py, start, cos(vars->POV - start) * current_len);
		vars->current_ray = make_angle(start);
		create_walls(vars, cos(vars->POV - start) * current_len, num_wall);
		start += ((M_PI / 3) / vars->s_width);
		num_wall++;
	}
    return (0);
}