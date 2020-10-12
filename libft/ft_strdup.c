/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:04:07 by efumiko           #+#    #+#             */
/*   Updated: 2020/08/18 23:35:35 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	size;
	char	*res;

	size = ft_strlen(src) + 1;
	res = (char*)malloc(size * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, src, size);
	return (res);
}
