#include "libft.h"

t_list	*ft_lst_find(t_list *lst, void *data_ref, int (*cmp)())
{
	while (lst)
	{
		if (cmp(lst->content, data_ref) == 0)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
