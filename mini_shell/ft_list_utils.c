#include "mini_parser.h"

/* int		ft_atoi(t_cub *cub, const char *nptr)
{
	int d;
	int k;

	k = 0;
	d = 1;
	while ((nptr[cub->index] == ' ') || (nptr[cub->index] == '\n') || (nptr[cub->index] == '\f')
	|| (nptr[cub->index] == '\v') || (nptr[cub->index] == '\r') || (nptr[cub->index] == '\t'))
		cub->index++;
	if ((nptr[cub->index] == '+') || (nptr[cub->index] == '-'))
	{
		if (nptr[cub->index] == '-')
			d *= -1;
		cub->index++;
	}
	while (nptr[cub->index] >= '0' && nptr[cub->index] <= '9')
	{
		k = k * 10 + (nptr[cub->index] - '0');
		cub->index++;
	}
	if (nptr)
		cub->index++;
	return (k * d);
} */

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
	new->cmd = ft_substr(line, shell->start, shell->end - shell->start);
	check_for_env(&new->cmd, shell);
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
		free((*list)->cmd);
		(*list)->cmd = NULL;
		free(*list);
		*list = NULL;
		(*list) = tmp;
	}
}
