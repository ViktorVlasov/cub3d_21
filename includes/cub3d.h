/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 23:35:31 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/10 22:34:58 by efumiko          ###   ########.fr       */
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

# define FLG_NONE   0b00000000
# define FLG_RES    0b00000001 // Resolution
# define FLG_NORTH  0b00000010 // North
# define FLG_SOUTH  0b00000100 // South
# define FLG_WEST   0b00001000 // West
# define FLG_EAST   0b00010000 // East
# define FLG_SPR    0b00100000 // Sprites
# define FLG_FLOOR  0b01000000 // Floor
# define FLG_CEIL   0b10000000 // Ceilling

#define RED 0x00FF0000
#define BLACK 0x00000000
#define GREEN 0x0000FF00
# define BUFFER_SIZE 4
# define BLOCK_SIZE 64

# define screenWidth 1920
# define screenHeight 1080

typedef struct  s_txtr
{
	char    	*no_texture;
	char    	*so_texture;
	char    	*we_texture;
	char    	*ea_texture;
	char    	*sprite_texture;
}               t_txtr;

typedef struct  s_params {
	int    		resolution[2];
	int    		floor_color;
	int    		ceilling_color;
	char   		**map;
	int			len_x;
	int			len_y;
}               t_params;

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

/* Parser */

int	        get_next_line(int fd, char **line);
int         get_amount_line(char **lines);
int         parser(t_params *params, t_txtr *data_cub, int fd);
int         parse_resolution(t_params *params, char **parsed_line, unsigned char *flags);
int         parse_textures(t_txtr *textures, char **parsed_line, unsigned char *flags);
int         parse_params(t_params *params, char **parsed_line, unsigned char *flags);
char        **get_map(int fd, t_params *params);
void        ft_free_array(char ***ar);

int		    ft_pos(char **map);
int		    ft_choice(char c, char *str);
int		    ft_choice_mass(char **map, char *set);
void        free_all(char *line, t_list *head);
int		    ft_full_map(char **map);

/* Raycasting */

int         start(t_params *params, t_txtr *textures, int screen);

void        t_draw_map(t_data *img, char **map);
void        my_mlx_pixel_put(t_data *data, int x, int y, int color);
void        my_mlx_draw_square(t_data *data, int x1, int y1, int color);

int	        get_coordinates(t_vars *vars);
int         cast_ray(t_vars *vars);

#endif