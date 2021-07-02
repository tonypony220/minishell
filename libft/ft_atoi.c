/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:36:16 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:38:58 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(char *str)
{
	int		sign;
	long	num;

	num = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	sign = (*str == '-') ? -1 : 1;
	(*str == '-' || *str == '+') ? str++ : str;
	while (*str >= '0' && *str <= '9')
	{
		if ((num = num * 10 + *str++ - '0') < 0)
			return (sign > 0 ? -1 : 0);
	}
	return ((int)num * sign);
}