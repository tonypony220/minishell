/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 00:02:39 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/15 00:02:50 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*list;

	list = *lst;
	while (list)
	{
		tmp = list->next;
		ft_lstdelone(list, del);
		list = tmp;
	}
	*lst = 0;
}
