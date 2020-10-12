/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 18:27:00 by efumiko           #+#    #+#             */
/*   Updated: 2020/05/24 10:28:47 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t sz;

	if (*little == '\0')
		return ((char *)big);
	sz = ft_strlen(little);
	while (*big && sz <= len)
	{
		if (ft_strncmp(big, little, sz) == 0)
			return ((char*)big);
		++big;
		--len;
	}
	return (NULL);
}
