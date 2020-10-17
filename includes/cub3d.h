/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 23:35:31 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/17 17:09:11 by ddraco           ###   ########.fr       */
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
# define FOV (M_PI / 3) 

# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define Q_KEY 12
# define RIGHT_KEY 124
# define LEFT_KEY 123

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
    int         img_width;
    int         img_height;
}               t_data;

typedef struct  s_images
{
    t_data      n_img;
    t_data      s_img;
    t_data      w_img;
    t_data      e_img;
    t_data      sprite_img;
}               t_images;

typedef struct  s_sprite
{
    double         sprite_x;
    double         sprite_y;
    double         sprite_dist;
	t_data         img_sprite;
}               t_sprite;

typedef struct  s_vars {
    t_images    textur;

    void        *mlx;
    void        *win_mlx;
    t_data      img;
    
    int         Px;
    int         Py;
    double      POV;
    double      current_ray;
    
    double      Xa;
    double      Ya;

    int         s_width;
    int         s_height;

    int         len_x;
    int         len_y;
    char        **map;

    double      offset_x_hor;
    double      offset_y_vert;
    
    t_sprite    *sprites;
    int    		floor_color;
	int    		ceilling_color;
    int         sprites_amount;
    double         *ray_length;

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

void        get_sprite_cord(t_vars *vars);
void	    ft_count_sprites(t_vars *vars);
int			ft_error(int flag);

/* Raycasting */

int         start(t_params *params, t_txtr *textures, int screen);

void        t_draw_map(t_data *img, char **map);
void        my_mlx_pixel_put(t_data *data, int x, int y, int color);
void        my_mlx_draw_square(t_data *data, int x1, int y1, int color);

int	        get_coordinates(t_vars *vars);
int         cast_ray(t_vars *vars);

int         my_mlx_pixel_get_color(t_data *data, int x, int y);

void	    create_bmp(t_vars *vars);
void        print_sprite(t_vars *vars, int num_sprite);
void		sort_sprites(t_vars *vars);

#endif