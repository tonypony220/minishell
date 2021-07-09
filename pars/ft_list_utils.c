#include "../minishell.h"

t_token	*token_lstlast(t_token *lst)

{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

t_token	*token_lstadd(t_token **lst, char *line, t_shell *shell)
{
	t_token	*first;
	t_token	*new;

	if (!line)
		return (NULL);
	new = (t_token*)malloc(sizeof(*new));
	if (new == NULL)
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

int		token_lstsize(t_token *lst)
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

void	token_lstclear(t_token **list)
{
	t_token	*tmp;

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
