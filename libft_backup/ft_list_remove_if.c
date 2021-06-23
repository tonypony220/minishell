/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmariana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:58:13 by gmariana          #+#    #+#             */
/*   Updated: 2020/09/23 15:32:43 by gmariana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *prev;
t_list *curr;
t_list *tmp;

void	free_curr(void (*free_fct)(void *))
{
	free_fct(curr->content);
	free(curr);
}

void	slide_next(void)
{
	prev = curr;
	curr = curr->next;
}

void	ft_list_remove_if(t_list **lst, 
							void *data_ref, 
							int (*cmp)(),
							void (*free_fct)(void *))
{
	curr = *lst;
	while (curr && (cmp(curr->content, data_ref) == 0))
	{
		*lst = curr->next;
		free_curr(free_fct);
		curr = *lst;
	}
	if (!curr || !curr->next)
		return ;
	slide_next();
	while (curr)
	{
		if (cmp(curr->content, data_ref) == 0)
		{
			tmp = curr->next;
			free_curr(free_fct);
			prev->next = tmp;
			curr = tmp;
		}
		else
			slide_next();
	}
}
