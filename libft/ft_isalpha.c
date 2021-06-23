/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:42:50 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:43:07 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_isupper(int c)
{
	return (c >= 65 && c <= 90);
}

static int		ft_islower(int c)
{
	return (c >= 97 && c <= 122);
}

int				ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
