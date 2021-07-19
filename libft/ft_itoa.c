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

char	*ft_itoa(int n)
{
	int		len;
	int		tmp;
	char	*str;
	int		sign;

	tmp = n;
	sign = 1 - 2 * (n < 0);
	len = 0;
	while (tmp && len++)
		tmp /= 10;
	(sign > 0) || len++;
	str = malloc(sizeof(char) * len + 1);
	if (str)
	{
		str[len] = '\0';
		while (len--)
		{
			(((sign < 0 && !len) && (str[len] = '-'))
			 || (str[len] = n % 10 * sign + '0'));
			n = n / 10;
		}
	}
	return (str);
}
