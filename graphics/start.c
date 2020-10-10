/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 23:35:22 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/10 22:29:49 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int     start(t_params *params, t_txtr *textures, int screen)
{
    t_vars vars;
    
    /*
    * Инициализация переменных, minilibx
    */
    vars.mlx = mlx_init();
    vars.s_width = params->resolution[0];
    vars.s_height = params->resolution[1];
    vars.len_x = params->len_x;
    vars.len_y = params->len_y;
    vars.map = params->map;
    vars.win_mlx = mlx_new_window(vars.mlx, vars.s_width, vars.s_height, "Cub3D");
    vars.img.img = mlx_new_image(vars.mlx, vars.s_width, vars.s_width);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
    get_coordinates(&vars);
    /*
    * Отрисовка карты, отрисовка игрока, отрисовка лучей.
    */
    // t_draw_map(&vars.img, vars.map);
    // my_mlx_pixel_put(&(vars.img), vars.Px, vars.Py, GREEN);
    cast_ray(&vars);
    
    mlx_put_image_to_window(vars.mlx, vars.win_mlx, vars.img.img, 0, 0);
    
    /* 
    * Обработка нажатий клавиш.
    */
    mlx_hook(vars.win_mlx, 17, 0, ft_close, &vars);
    mlx_hook(vars.win_mlx, 2, 0L, events, &vars);
    mlx_loop(vars.mlx);
    return 0;   
}