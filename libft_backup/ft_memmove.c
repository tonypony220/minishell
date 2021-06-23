/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:03:37 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:37:28 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;

	dst_p = (unsigned char*)dst;
	src_p = (unsigned char*)src;
	if (!src && !dst)
		return (0);
	if (src_p >= dst_p || dst_p >= (src_p + len))
	{
		while (len--)
		{
			*dst_p++ = *src_p++;
		}
	}
	else
	{
		src_p += len - 1;
		dst_p += len - 1;
		while (len--)
		{
			*dst_p-- = *src_p--;
		}
	}
	return (dst);
}
