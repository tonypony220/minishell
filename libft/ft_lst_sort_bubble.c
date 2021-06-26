#include "libft.h"

void	ft_lst_sort_bubble(t_list **lst, int (*cmp)())
{
	int		swapped;
	t_list	*ptr;
	void	*tmp;

	if (!*lst)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = *lst;
		while (ptr->next)
		{
			if (cmp(ptr->content, ptr->next->content) > 0)
			{
				swapped = 1;
				tmp = ptr->content;
				ptr->content = ptr->next->content;
				ptr->next->content = tmp;
			}
			ptr = ptr->next;
		}
	}
}
