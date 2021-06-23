/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmariana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 15:56:05 by gmariana          #+#    #+#             */
/*   Updated: 2020/09/23 15:56:39 by gmariana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list *ptr;

	ptr = *begin_list1;
	if (!ptr)
	{
		*begin_list1 = begin_list2;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = begin_list2;
}
