/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:03:40 by efumiko           #+#    #+#             */
/*   Updated: 2020/05/24 11:35:54 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*to;
	unsigned char	*from;

	to = (unsigned char*)dst;
	from = (unsigned char*)src;
	if (dst || src)
	{
		while (n--)
		{
			*to = *from;
			++to;
			++from;
		}
		return (dst);
	}
	return (NULL);
}
