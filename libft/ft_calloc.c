/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:02:42 by efumiko           #+#    #+#             */
/*   Updated: 2020/05/24 11:29:51 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*arr;

	if (size != 0 && (((num * size) / size) != num))
		return (NULL);
	arr = malloc(size * num);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, size * num);
	return (arr);
}
