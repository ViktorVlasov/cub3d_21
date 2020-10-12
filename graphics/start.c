/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 23:35:22 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/12 23:08:50 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int     start(t_params *params, t_txtr *textures, int screen)
{
    t_vars      vars;
    t_sprite    *sprites;
    
    /*
    * Инициализация переменных, minilibx
    */
    int max_width;
    int max_height;
   
    
    
    // vars.mlx = mlx_init();
    // mlx_get_screen_size(vars.mlx, &max_width, &max_height);
    
    // vars.s_width = params->resolution[0] >= max_width ? max_width : params->resolution[0];
    // vars.s_height = params->resolution[1] >= max_height ? max_height : params->resolution[1];
    // vars.len_x = params->len_x;
    // vars.len_y = params->len_y;
    // vars.ceilling_color = params->ceilling_color;
    // vars.floor_color = params->floor_color;
    vars.map = params->map;
    // vars.win_mlx = mlx_new_window(vars.mlx, vars.s_width, vars.s_height, "Cub3D");
    // vars.img.img = mlx_new_image(vars.mlx, vars.s_width, vars.s_height);
    // vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
    
    // vars.textur.n_img.img = mlx_xpm_file_to_image(vars.mlx, textures->no_texture, &vars.textur.n_img.img_width, &vars.textur.n_img.img_height);
    // vars.textur.n_img.addr = mlx_get_data_addr(vars.textur.n_img.img, &vars.textur.n_img.bits_per_pixel, &vars.textur.n_img.line_length, &vars.textur.n_img.endian);
    
    // vars.textur.s_img.img = mlx_xpm_file_to_image(vars.mlx, textures->so_texture, &vars.textur.s_img.img_width, &vars.textur.s_img.img_height);
    // vars.textur.s_img.addr = mlx_get_data_addr(vars.textur.s_img.img, &vars.textur.s_img.bits_per_pixel, &vars.textur.s_img.line_length, &vars.textur.s_img.endian);
    
    // vars.textur.w_img.img = mlx_xpm_file_to_image(vars.mlx, textures->we_texture, &vars.textur.w_img.img_width, &vars.textur.w_img.img_height);
    // vars.textur.w_img.addr = mlx_get_data_addr(vars.textur.w_img.img, &vars.textur.w_img.bits_per_pixel, &vars.textur.w_img.line_length, &vars.textur.w_img.endian);
    
    // vars.textur.e_img.img = mlx_xpm_file_to_image(vars.mlx, textures->ea_texture, &vars.textur.e_img.img_width, &vars.textur.e_img.img_height);
    // vars.textur.e_img.addr = mlx_get_data_addr(vars.textur.e_img.img, &vars.textur.e_img.bits_per_pixel, &vars.textur.e_img.line_length, &vars.textur.e_img.endian);
    
    // vars.offset_y_vert = -1;
    // vars.offset_x_hor = -1;
    // get_coordinates(&vars);

    sprites = get_sprite_cord(&vars);
    
    for (int i = 0; i < 4; i++)
    {
        printf("cord x - %d,cord y - %d\n", sprites[i].sprite_x / 64, sprites[i].sprite_y / 64);
    }

    // /*
    // * Отрисовка карты, отрисовка игрока, отрисовка лучей.
    // */
    // // t_draw_map(&vars.img, vars.map);
    // // my_mlx_pixel_put(&(vars.img), vars.Px, vars.Py, GREEN);
    // cast_ray(&vars);
    
    // mlx_put_image_to_window(vars.mlx, vars.win_mlx, vars.img.img, 0, 0);

    
    // /* 
    // * Обработка нажатий клавиш.
    // */
    // mlx_hook(vars.win_mlx, 17, 0, ft_close, &vars);
    // mlx_hook(vars.win_mlx, 2, 0L, events, &vars);
    // mlx_loop(vars.mlx);
    return 0;   
}