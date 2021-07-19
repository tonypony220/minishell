#include "libft.h"

/* function acts like generator:
 * returning each element */

void	*ft_lstgen(t_list *lst, void *(*f)(void *))
{
	static t_list	*p;
	static t_list	*mem;
	static int		virgin;
	t_list			*tmp;

	(mem == lst) || (virgin = 0);
	virgin == 0 && (++virgin) && (p = lst) && (mem = lst);
	if (!p)
	{
		virgin = 0;
		return (p);
	}
	tmp = p;
	p = p->next;
	return (f(tmp->content));
}
