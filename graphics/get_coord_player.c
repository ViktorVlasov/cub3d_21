/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 01:18:00 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/17 22:02:22 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_pov(char *direction, double *pov)
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

int			get_coordinates(t_vars *vars)
{
	int		i;
	int		j;
	char	*direction;

	i = 0;
	j = 0;
	while (vars->map[i] != NULL)
	{
		j = 0;
		while (vars->map[i][j])
		{
			if ((direction = ft_strchr("NSWE", vars->map[i][j])) != NULL)
			{
				get_pov(direction, &(vars->pov));
				vars->px = j * BLOCK_SIZE + BLOCK_SIZE / 2;
				vars->py = i * BLOCK_SIZE + BLOCK_SIZE / 2;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void		ft_count_sprites(t_vars *vars)
{
	int i;
	int j;

	vars->sprites_amount = 0;
	i = 0;
	j = 0;
	while (vars->map[i] != NULL)
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '2')
				vars->sprites_amount++;
			j++;
		}
		i++;
	}
}

void		get_sprite_cord(t_vars *vars)
{
	int x;
	int i;
	int j;

	i = 0;
	x = 0;
	while (vars->map[i] != NULL || (x < vars->sprites_amount))
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '2')
			{
				vars->sprites[x].sprite_x = j * BLOCK_SIZE + BLOCK_SIZE / 2;
				vars->sprites[x].sprite_y = i * BLOCK_SIZE + BLOCK_SIZE / 2;
				vars->sprites[x].sprite_dist =
				sqrt(pow(vars->px - vars->sprites[x].sprite_x, 2) \
				+ pow(vars->py - vars->sprites[x].sprite_y, 2));
				x++;
			}
			j++;
		}
		i++;
	}
}
