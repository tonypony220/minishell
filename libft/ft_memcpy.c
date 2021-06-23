/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:05:33 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:05:53 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	if (dst || src)
	{
		while (n--)
			((unsigned char*)dst)[n] = ((unsigned char*)src)[n];
	}
	return (dst);
}
