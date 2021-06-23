/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmariana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:15:42 by gmariana          #+#    #+#             */
/*   Updated: 2020/09/23 14:16:18 by gmariana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_reverse(t_list **begin_list)
{
	t_list *tmp;
	t_list *prev;
	t_list *curr;

	if (!*begin_list || !(*begin_list)->next)
		return ;
	prev = *begin_list;
	curr = prev->next;
	prev->next = 0;
	while (curr->next)
	{
		tmp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = tmp;
	}
	curr->next = prev;
	*begin_list = curr;
}
