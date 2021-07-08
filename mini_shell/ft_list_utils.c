#include "mini_parser.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}


t_list	*ft_lstadd(t_list **lst, char *line, t_shell *shell)
{
	t_list	*first;
	t_list	*new;

	if (!line)
		return (NULL);
	if (!(new = (t_list*)malloc(sizeof(*new))))
		return (0);
	new->token = ft_strdup(line);
	check_for_env(&new->token, shell);
	shell->flags.double_q = 0;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		first = *lst;
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = new;
		*lst = first;
	}
	return (new);
}

int		ft_lstsize(t_list *lst)
{
	int d;

	d = 0;
	while (lst)
	{
		d++;
		lst = lst->next;
	}
	return (d);
}

void	ft_lstclear(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->token);
		(*list)->token = NULL;
		free(*list);
		*list = NULL;
		(*list) = tmp;
	}
}
