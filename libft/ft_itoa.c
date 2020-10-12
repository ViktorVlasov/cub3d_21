/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 19:30:21 by efumiko           #+#    #+#             */
/*   Updated: 2020/05/24 11:30:03 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int len;

	len = n == 0 ? 1 : 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	dig_to_char(int n)
{
	if (n < 0)
		return (-1 * n + '0');
	return (n + '0');
}

char		*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		mark;

	mark = n < 0 ? 1 : 0;
	size = mark == 1 ? get_len(n) + 1 : get_len(n);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	while (size > mark)
	{
		size--;
		str[size] = dig_to_char(n % 10);
		n /= 10;
	}
	if (mark == 1)
	{
		size--;
		str[size] = '-';
	}
	return (str);
}
