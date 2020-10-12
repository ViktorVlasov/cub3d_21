/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 14:01:24 by efumiko           #+#    #+#             */
/*   Updated: 2020/05/24 11:31:06 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_res(char **res)
{
	int i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		res[i] = NULL;
		i++;
	}
	free(res);
}

static int	get_count_words(const char *str, char c)
{
	int count_words;
	int i;

	count_words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
		{
			count_words++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count_words);
}

static char	**alloc_memarr(char **result, char *strclear, char c)
{
	int	i;
	int	count_symb;
	int	num_str;

	i = 0;
	num_str = 0;
	while (strclear[i] != '\0')
	{
		count_symb = 0;
		while (strclear[i] != c && strclear[i] != '\0')
		{
			count_symb++;
			i++;
		}
		while (strclear[i] == c && strclear[i] != '\0')
			i++;
		if (!(result[num_str] = (char*)malloc((count_symb + 1) * sizeof(char))))
		{
			free_res(result);
			result = NULL;
			return (NULL);
		}
		num_str++;
	}
	return (result);
}

static char	**fill_arr(char **result, char *strclear, char c)
{
	int	i;
	int	indx_str;
	int	num_str;

	i = 0;
	indx_str = 0;
	num_str = 0;
	while (strclear[i] != '\0')
	{
		while (strclear[i] != c && strclear[i] != '\0')
		{
			result[num_str][indx_str] = strclear[i];
			i++;
			indx_str++;
		}
		while (strclear[i] == c && strclear[i] != '\0')
			i++;
		result[num_str][indx_str] = '\0';
		num_str++;
		if (strclear[i] == c && strclear[i] != '\0')
			i++;
		indx_str = 0;
	}
	return (result);
}

char		**ft_split(char const *s, char c)
{
	char	chr[2];
	char	*strclear;
	int		count_strings;
	char	**result;

	if (!s)
		return (NULL);
	chr[0] = c;
	chr[1] = '\0';
	strclear = ft_strtrim(s, chr);
	count_strings = get_count_words(s, c);
	result = (char**)malloc((count_strings + 1) * sizeof(char*));
	if (result == NULL)
		return (NULL);
	result[count_strings] = NULL;
	alloc_memarr(result, strclear, c);
	fill_arr(result, strclear, c);
	free(strclear);
	strclear = NULL;
	return (result);
}
