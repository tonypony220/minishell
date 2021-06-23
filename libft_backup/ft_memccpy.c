/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:55:01 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:01:38 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n--)
	{
		*((unsigned char*)dst) = *((unsigned char*)src);
		if (*((unsigned char*)src) == (unsigned char)c)
			return ((void *)++dst);
		src++;
		dst++;
	}
	return (0);
}
