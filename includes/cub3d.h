/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 23:35:31 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/10 16:38:07 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include "libft.h"
# include "mlx.h"

#define RED 0x00FF0000
#define BLACK 0x00000000
#define GREEN 0x0000FF00
# define BUFFER_SIZE 4
# define BLOCK_SIZE 64

# define screenWidth 1920
# define screenHeight 1080

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_vars {
    void        *mlx;
    void        *win_mlx;
    t_data      img;
    
    int         Px;
    int         Py;
    double      POV;
    
    double      Xa;
    double      Ya;

    int         s_width;
    int         s_height;

    int         len_x;
    int         len_y;
    char        **map;
}               t_vars;

int	        get_next_line(int fd, char **line);

int		    ft_close(t_vars *vars);
int         events(int keycode, t_vars *vars);


void        t_draw_map(t_data *img, char **map);
void        my_mlx_pixel_put(t_data *data, int x, int y, int color);
void        my_mlx_draw_square(t_data *data, int x1, int y1, int color);

int	        get_coordinates(t_vars *vars);
int         cast_ray(t_vars *vars);

#endif