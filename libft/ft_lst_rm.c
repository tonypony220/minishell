#include "libft.h"

void	ft_lst_rm(t_list **lst, void *data_ref, 
					int (*cmp)(), void (*del)(void *))
{

	t_list *prev;
	t_list *curr;

	curr = *lst;
	prev = NULL;
	while (curr)
	{
			
		if (cmp(curr->content, data_ref) == 0)
		{
			prev && (prev->next = curr->next);
			!prev && (*lst = curr->next);
			ft_lst_delone(curr, del);
			!prev && (curr = *lst);
			prev && (curr = prev->next);
			continue ;
		}
		else
			prev = curr;
		curr = curr->next;
	}
}
