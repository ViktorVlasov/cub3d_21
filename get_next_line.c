/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 11:33:07 by efumiko           #+#    #+#             */
/*   Updated: 2020/10/08 00:15:46 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static char	*ft_check_rem(char **remainder, char **line, int *error_flag)
{
	char *p_n;

	p_n = NULL;
	if (*remainder)
		if ((p_n = ft_strchr(*remainder, '\n')))
		{
			*p_n = '\0';
			if ((*line = ft_strdup(*remainder)) == NULL)
				*error_flag = 1;
			ft_strcpy(*remainder, ++p_n);
		}
		else
		{
			if ((*line = ft_strdup(*remainder)) == NULL)
				*error_flag = 1;
			free(*remainder);
			*remainder = NULL;
		}
	else
	{
		if ((*line = ft_strdup("")) == NULL)
			*error_flag = 1;
	}
	return (p_n);
}

static int	ft_error_free(char **line, char **remainder, char **p_n)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	if (*remainder)
	{
		free(*remainder);
		*remainder = NULL;
	}
	if (*p_n)
	{
		free(*p_n);
		*p_n = NULL;
	}
	return (-1);
}

static int	ft_add_remainder(char **line, char **remainder, char **p_n)
{
	**p_n = '\0';
	if ((*remainder = ft_strdup(++(*p_n))) == NULL)
		return (ft_error_free(line, remainder, p_n));
	return (1);
}

static int	ft_join_buf(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	if (!(*line = ft_strjoin(*line, buf)))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char		*remainder;
	char			buf[BUFFER_SIZE + 1];
	int				count_byte;
	char			*p_n;
	int				error_flag;

	error_flag = 0;
	if (BUFFER_SIZE < 1 || fd < 0 || !line || (read(fd, buf, 0) < 0))
		return (-1);
	p_n = ft_check_rem(&remainder, line, &error_flag);
	if (error_flag)
		return (ft_error_free(line, &remainder, &p_n));
	while (!p_n && (count_byte = read(fd, buf, BUFFER_SIZE)))
	{
		buf[count_byte] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
			if (ft_add_remainder(line, &remainder, &p_n) == (-1))
				return (-1);
		if (ft_join_buf(line, buf) == (-1))
			return (ft_error_free(line, &remainder, &p_n));
	}
	return ((p_n) ? 1 : 0);
}
