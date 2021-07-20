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

void	flag_check(t_token **token, t_shell *shell)
{
	shell->flags.double_q = 0;
	if (shell->flags.has_redir == 1)
	{
		(*token)->redir = 1;
		(*token)->redir_type = shell->flags.redir_type;
		shell->redir_count++;
		shell->flags.has_redir = 0;
	}
	if (shell->in_compose)
		(*token)->redir_type = shell->in_compose;
}

t_token	*token_lstadd(t_token **lst, char *line, t_shell *shell)
{
	t_token	*first;
	t_token	*new;

	if (!line)
		return (NULL);
	new = (t_token *)ft_calloc(sizeof(*new), 1);
	if (new == NULL)
		return (0);
	new->token = ft_strdup(line);
	flag_check(&new, shell);
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

int	token_lstsize(t_token *lst)
{
	int	d;

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
		*list = tmp;
	}
}
