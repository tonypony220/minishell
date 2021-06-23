/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:55:26 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:56:00 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	int		len;
	int		tmp;
	char	*str;
	int		sign;

	tmp = n;
	sign = n >= 0 ? 1 : -1;
	len = 1;
	while (tmp /= 10)
		len++;
	(sign > 0) ? len : len++;
	if ((str = malloc(sizeof(char) * len + 1)))
	{
		str[len] = '\0';
		while (len--)
		{
			str[len] = (sign < 0 && !len) ? '-' : n % 10 * sign + '0';
			n = n / 10;
		}
	}
	return (str);
}
