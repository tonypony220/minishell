#include "mini_parser.h"

t_shlist	*s_sh_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}


t_shlist	*ft_lstadd(t_list **lst, char *line, t_shell *shell)
{
	t_shlist	*first;
	t_shlist	*new;

	if (!line)
		return (NULL);
	if (!(new = (t_shlist*)malloc(sizeof(*new))))
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

int		s_sh_lstsize(t_shlist *lst)
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

void	ft_sh_lst_clear(t_shlist **list)
{
	t_shlist	*tmp;

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
