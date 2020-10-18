/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:14:31 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/19 00:07:44 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_choice_mass(char **map, char *set)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(set, map[i][j]) == NULL)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_list	*map_to_list(int fd, char **line, t_params *params,\
						int check_empty)
{
	t_list	*head;

	head = NULL;
	while (get_next_line(fd, line))
	{
		if ((int)ft_strlen(*line) > params->len_x)
			params->len_x = (int)ft_strlen(*line);
		if ((*line)[0] == '\0' && check_empty == 1)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
		else if ((*line)[0] != '\0')
		{
			check_empty = 1;
			ft_lstadd_back(&head, ft_lstnew(*line));
		}
		else if (*line)
			free(*line);
	}
	if ((int)ft_strlen(*line) > params->len_x)
		params->len_x = (int)ft_strlen(*line);
	ft_lstadd_back(&head, ft_lstnew(*line));
	return (head);
}

char	**list_to_arr(char **line, t_list *head, t_params *params)
{
	int		i;
	char	**map;
	t_list	*tmp;

	tmp = head;
	params->len_y = ft_lstsize(head);
	if ((map = ft_calloc(ft_lstsize(head) + 1, sizeof(char*))) == NULL)
	{
		ft_lstclear(&head, free);
		return (NULL);
	}
	i = 0;
	while (tmp)
	{
		map[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	ft_lstclear(&head, free);
	return (map);
}

char	**get_map(int fd, t_params *params)
{
	char	**map;
	char	*line;
	t_list	*head;

	if (!(head = map_to_list(fd, &line, params, 0)))
		return (NULL);
	if (!(map = list_to_arr(&line, head, params)))
		return (NULL);
	if (ft_pos(map) && ft_full_map(map) && ft_choice_mass(map, " 012SNWE"))
		return (map);
	else
	{
		ft_free_array(&map);
		return (NULL);
	}
}

int		ft_full_map(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] != '1' && map[y][x] != ' ')
			{
				if (y - 1 < 0
					|| (int)ft_strlen(map[y - 1]) <= x || map[y - 1][x] == ' '
					|| (int)ft_strlen(map[y + 1]) <= x
					|| map[y][x - 1] == ' ' || x + 1 >= (int)ft_strlen(map[y])
					|| y + 1 >= (int)get_amount_line(map)
					|| map[y][x + 1] == ' '
					|| map[y + 1][x] == ' ' || x - 1 < 0)
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
