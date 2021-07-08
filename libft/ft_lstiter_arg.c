#include "libft.h"

void	ft_lstiter_arg(t_list *lst, void (*f)(), void *data)
{
	while (lst)
	{
		f(lst->content, data);
		lst = lst->next;
	}
}
