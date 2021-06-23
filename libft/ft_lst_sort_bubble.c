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
