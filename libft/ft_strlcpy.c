/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:09:03 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:09:28 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t len;

	if (!src || !dst)
		return (0);
	len = ft_strlen(src);
	if (dstsize)
	{
		while (--dstsize)
		{
			if (*src && len)
				*dst++ = *src++;
		}
		*dst = '\0';
	}
	return (len);
}
