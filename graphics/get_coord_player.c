/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 01:18:00 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/10 22:16:41 by efumiko          ###   ########.fr       */
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