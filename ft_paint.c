/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 01:06:45 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/08 01:10:17 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)); // Находим адрес пикселя
    *(unsigned int*)dst = color; // Закрашиваем его
}

void            my_mlx_draw_square(t_data *data, int x1, int y1, int color)
{
    int x_up;
    int y_up;
    int tmp;

    tmp = x1;
    x_up = x1 + BLOCK_SIZE;
    y_up = y1 + BLOCK_SIZE;
    while (y1 < y_up)
    {
        x1 = tmp;
        while (x1 < x_up)
        {
            my_mlx_pixel_put(data, x1, y1, color);
            x1++;
        }
        y1++;
    }
}

void t_draw_map(t_data *img, char **map)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int elem = 0;
    while (map[i])
    {
        elem = 0;
        x = 0;
        while (map[i][elem])
        {  
            if (map[i][elem] == '1')
                my_mlx_draw_square(img, x, y, RED);
            else
                my_mlx_draw_square(img, x, y, BLACK);
            x += BLOCK_SIZE;
            elem++;
        }
        y += BLOCK_SIZE;
        i++;
    }
}