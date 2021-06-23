/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:59:15 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:59:33 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*ret;

	if ((ret = (t_list*)malloc(sizeof(t_list))))
	{
		ret->content = content;
		ret->next = 0;
	}
	return (ret);
}
