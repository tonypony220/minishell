/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmariana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 16:18:32 by gmariana          #+#    #+#             */
/*   Updated: 2020/09/23 16:36:04 by gmariana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	int		swapped;
	t_list	*ptr;
	void	*tmp;

	if (!*begin_list)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = *begin_list;
		while (ptr->next)
		{
			if (cmp(ptr->data, ptr->next->data) > 0)
			{
				swapped = 1;
				tmp = ptr->data;
				ptr->data = ptr->next->data;
				ptr->next->data = tmp;
			}
			ptr = ptr->next;
		}
	}
}
