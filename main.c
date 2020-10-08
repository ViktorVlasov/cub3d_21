/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 23:35:22 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/08 01:15:31 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

char  **save_map(int size, t_list **tmp)
{
    int i = 0;
    char **map = ft_calloc(size + 1, sizeof(char *));
    t_list *list = *tmp;
    while(list)
    {
        map[i] = ft_strdup(list->content);
        list = list->next;
        i++;
    }
    map[i] = NULL;  //  Может быть нужен 0, хотя это обращение к строке...
    i = 0;
    
    return(map);
}

int main(int argc, char **argv)
{
    int fd;
    char *line = NULL;
    t_list *tmp = NULL;
    t_vars vars;

    /* 
    * Считывание карты и добавление её в массив
    */
    fd = open(argv[1], O_RDONLY);
    while (get_next_line(fd, &line) > 0)
        ft_lstadd_back(&tmp, ft_lstnew(line));
    ft_lstadd_back(&tmp, ft_lstnew(line));
    vars.map = save_map(ft_lstsize(tmp), &tmp);


    /*
    * Инициализация переменных, minilibx
    */
    vars.mlx = mlx_init();
    vars.win_mlx = mlx_new_window(vars.mlx, screenWidth, screenHeight, "test");
    vars.img.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
    
    /*
    * Отрисовка карты, отрисовка игрока, отрисовка лучей.
    */
    t_draw_map(&vars.img, vars.map);
    
    mlx_put_image_to_window(vars.mlx, vars.win_mlx, vars.img.img, 0, 0);
    
    /* 
    * Обработка нажатий клавиш.
    */
    mlx_hook(vars.win_mlx, 17, 0, ft_close, &vars);
    mlx_hook(vars.win_mlx, 2, 0L, events, &vars);
    mlx_loop(vars.mlx);
    return 0;   
}