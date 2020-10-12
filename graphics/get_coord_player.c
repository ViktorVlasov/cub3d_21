/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 01:18:00 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/12 22:53:39 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void get_pov(char *direction, double *pov)
{
	if (*direction == 'S')
		*pov = 3 * M_PI_2;
	if (*direction == 'N')
		*pov = M_PI_2;
	if (*direction == 'W')
		*pov = M_PI;
	if (*direction == 'E')
		*pov = 0;
}

int	get_coordinates(t_vars *vars)
{
	int i;
	int j;
	char *direction;

	i = 0;
	j = 0;
	while (vars->map[i] != NULL)
	{
		j = 0;
		while (vars->map[i][j])
		{
			if ((direction = ft_strchr("NSWE", vars->map[i][j])) != NULL)
			{	
				get_pov(direction, &(vars->POV));
				vars->Px = j * BLOCK_SIZE + BLOCK_SIZE / 2;
				vars->Py = i * BLOCK_SIZE + BLOCK_SIZE / 2;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

t_sprite *get_sprite_cord(t_vars *vars)
{
	t_sprite *sprites;
	int i;
	int j;
	int counter;

	counter = 0;
	i = 0;
	j = 0;
	while (vars->map[i] != NULL)
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '2')
				counter++;
			j++;
		}
		i++;
	}
	sprites = (t_sprite *)malloc(sizeof(t_sprite) * counter);
	i = 0;
	counter = 0;
	while (vars->map[i] != NULL)
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '2')
				{
					sprites[counter].sprite_x = j * BLOCK_SIZE + BLOCK_SIZE / 2;
					sprites[counter].sprite_y = i * BLOCK_SIZE + BLOCK_SIZE / 2;  
					counter++;
				}
			j++;
		}
		i++;
	}
	return (sprites);
}