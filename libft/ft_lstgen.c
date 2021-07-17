#include "libft.h"
//
//void	*ft_lstgen(t_list **lst, void *(*f)(void *))
//{
//	static t_list	**p;
//	t_list			*tmp;
//
//	p == 0 && (p = lst);
//	if (!*p)
//		return (*p);
//	//printf("\t\t\t%p p %p tmp\n", *p, tmp);
//	tmp = *p;
//	printf("\t%p p %p p->next\n", *p, (*p)->next);
//	*p = (*p)->next;	
//	return (tmp->content);
//	//return (f(tmp->content));
//}


void	*ft_lstgen(t_list *lst, void *(*f)(void *))
{
	static t_list	*p;
	static int		virgin;
	t_list	*tmp;

	//printf("\t%p p p->next\n", p );//(p)->next);
	virgin == 0 && (++virgin) && (p = lst);
	if (!p && !(virgin = 0))
		return (p);
	//printf("\t\t\t%p p %p tmp\n", *p, tmp);
	tmp = p;
	p = p->next;	
	//printf("\t%p p\n", p );//(p)->next);
	return (f(tmp->content));
	//return (f(tmp->content));
}
