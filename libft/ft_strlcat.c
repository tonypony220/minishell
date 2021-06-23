/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:09:43 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:10:56 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t					ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t				len;
	int					found;

	found = 0;
	len = ft_strlen(src);
	while (dstsize--)
	{
		if (*dst && !found && ++len)
			dst++;
		else if (*src && dstsize && ++found)
			*dst++ = *src++;
		else
		{
			*dst = '\0';
			break ;
		}
	}
	return (len);
}
