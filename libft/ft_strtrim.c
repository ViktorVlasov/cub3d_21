/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:20:31 by efumiko           #+#    #+#             */
/*   Updated: 2020/05/24 11:31:46 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_end_index(const char *s1, char const *set)
{
	size_t	index_set;
	size_t	end_index;

	index_set = 0;
	end_index = 0;
	if (ft_strlen(s1) != 0)
	{
		end_index = ft_strlen(s1) - 1;
		while (set[index_set] != '\0')
		{
			if (s1[end_index] == set[index_set])
			{
				--end_index;
				index_set = 0;
			}
			else
				++index_set;
		}
	}
	return (end_index);
}

static int	get_start_index(const char *s1, char const *set)
{
	size_t	index_set;
	size_t	start;

	index_set = 0;
	start = 0;
	while (set[index_set] != '\0')
	{
		if (s1[start] == set[index_set])
		{
			++start;
			index_set = 0;
		}
		else
			++index_set;
	}
	return (start);
}

static char	*fill_newstr(char const *s1, size_t len_newstr)
{
	char	*newstr;
	size_t	index_newstr;

	newstr = (char*)malloc((len_newstr + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	index_newstr = 0;
	while (index_newstr < len_newstr)
	{
		newstr[index_newstr] = s1[index_newstr];
		++index_newstr;
	}
	newstr[index_newstr] = '\0';
	return (newstr);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	end_index;
	size_t	len_newstr;
	char	*newstr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (*s1 != '\0')
	{
		s1 = s1 + get_start_index(s1, set);
		end_index = get_end_index(s1, set);
		len_newstr = *s1 == 0 ? 0 : end_index + 1;
		newstr = fill_newstr(s1, len_newstr);
	}
	else
		newstr = ft_strdup("");
	return (newstr);
}
