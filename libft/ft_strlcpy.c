/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 12:27:30 by efumiko           #+#    #+#             */
/*   Updated: 2020/05/24 14:40:01 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t tmpsize;
	size_t i;

	if (!dst || !src)
		return (0);
	tmpsize = size;
	i = 0;
	while (src[i] != '\0' && tmpsize > 0)
	{
		dst[i] = src[i];
		tmpsize--;
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	else if (size > 0)
		dst[i - 1] = '\0';
	return (ft_strlen(src));
}
