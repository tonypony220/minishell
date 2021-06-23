/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:18:09 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:47:32 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *src)
{
	char	*tmp;
	char	*dup;

	if (!(dup = malloc(sizeof(*dup) * (ft_strlen((char*)src) + 1))))
		return (0);
	tmp = dup;
	while (*src)
		*tmp++ = *src++;
	*tmp = '\0';
	return (dup);
}
