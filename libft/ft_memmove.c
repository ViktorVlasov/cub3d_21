/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:03:43 by efumiko           #+#    #+#             */
/*   Updated: 2020/05/21 23:00:20 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*to;
	unsigned char	*from;

	if (dst || src)
	{
		to = (unsigned char*)dst;
		from = (unsigned char*)src;
		if (to < from)
			ft_memcpy(dst, src, len);
		else
		{
			to += len;
			from += len;
			while (len--)
			{
				*(--to) = *(--from);
			}
		}
		return (dst);
	}
	return (NULL);
}
