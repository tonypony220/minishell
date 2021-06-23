/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:49:39 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:50:40 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*tmp;

	str = 0;
	if (s1 && s2 && (str = malloc(sizeof(char) * \
					(ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1))))
	{
		tmp = str;
		while (*s1)
			*tmp++ = *s1++;
		while (*s2)
			*tmp++ = *s2++;
		*tmp = '\0';
	}
	return (str);
}
