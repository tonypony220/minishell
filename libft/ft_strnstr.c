/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:40:47 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:41:47 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_strnstr(const char *haystack, \
		const char *needle, size_t len)
{
	unsigned long int	needle_len;
	unsigned long int	i;

	needle_len = ft_strlen((char*)needle);
	if (!needle_len)
		return ((char*)haystack);
	while (*haystack && (int)(len-- - needle_len) >= 0)
	{
		i = needle_len;
		while (i--)
		{
			if (haystack[i] != needle[i])
				break ;
			if (!i)
				return ((char *)haystack);
		}
		haystack++;
	}
	return (0);
}
