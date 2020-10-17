/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:14:31 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/17 19:18:54 by efumiko          ###   ########.fr       */
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

t_list	*map_to_list(int fd, char **line, t_params *params)
{
	t_list	*head;
	int		check_empty;

	check_empty = 0;
	head = NULL;
	while (get_next_line(fd, line))
	{
		if ((int)ft_strlen(*line) > params->len_x)
			params->len_x = (int)ft_strlen(*line);
		if ((*line)[0] == '\0' && check_empty == 1)
		{
			free_all(*line, head);
			return (NULL);
		}
		if ((*line)[0] != '\0')
		{
			check_empty = 1;
			ft_lstadd_back(&head, ft_lstnew(*line));
		}
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

	params->len_y = ft_lstsize(head);
	if ((map = ft_calloc(ft_lstsize(head) + 1, sizeof(char*))) == NULL)
	{
		free_all(*line, head);
		return (NULL);
	}
	i = 0;
	while (head)
	{
		map[i] = ft_strdup(head->content);
		i++;
		head = head->next;
	}
	free_all(*line, head);
	return (map);
}

char	**get_map(int fd, t_params *params)
{
	char	**map;
	char	*line;
	t_list	*head;
	int		i;

	if (!(head = map_to_list(fd, &line, params)))
		return (NULL);
	if (!(map = list_to_arr(&line, head, params)))
		return (NULL);
	if (ft_pos(map) && ft_full_map(map) && ft_choice_mass(map, " 012SNWE"))
	{
		i = 0;
		while (map[i])
		{
			printf("Строка номер %d: %s\n", i, map[i]);
			i++;
		}
		return (map);
	}
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
