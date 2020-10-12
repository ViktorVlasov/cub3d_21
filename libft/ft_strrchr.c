/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:04:21 by efumiko           #+#    #+#             */
/*   Updated: 2020/05/23 11:23:29 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != 0)
		++i;
	while (s[i] != (char)c && i >= 0)
		--i;
	if (s[i] == (char)c)
		return ((char*)&s[i]);
	return (NULL);
}
