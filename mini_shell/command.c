#include "mini_parser.h"

static int		count_size(char **str)
{
	int i = 0;
	int j;

	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
			j++;
		i++;
	}
	return (i);
}

void	free_command(t_cmd **list)
{
	t_cmd	*tmp;
	int		i;
	int 	size;

	if (*list == NULL)
	{
		printf("??\n");
		return ;
	}
	while (*list)
	{
		i = 0;
		tmp = (*list)->next;
		size = count_size((*list)->cmd);
		while (size--)
			free((*list)->cmd[i++]);
		free((*list)->cmd);
		free(*list);
		*list = NULL;
		(*list) = tmp;
	}
}

void	print_command(t_shell *shell)
{
	int i = 0;
	int d = 0;
	t_cmd *tmp;

	tmp = shell->cmd;
	while (tmp)
	{
		printf("cmd #%d >>> ", d);
		while (tmp->cmd[i] != NULL)
			printf("%s ", tmp->cmd[i++]);
		printf("\n\tPIPE IN [%d] -- PIPE OUT [%d] -- PIPE NUMBER [%d]\n", tmp->pipe[0], tmp->pipe[1], tmp->_pipe);
		tmp = tmp->next;
		d++;
	}
}

int		compose_command(t_cmd **lst, t_list *token, t_shell *shell, int size)
{
	t_cmd	*first;
	t_cmd	*new;
	int		i;

	i = 0;
	if (token == NULL)
		return (0);
	if (!(new = (t_cmd*)malloc(sizeof(*new))))
		return (0);
	new->cmd = (char **)malloc((size + 1)  * sizeof(char *));
	if (new->cmd == NULL)
		return (-1);
	while (token)
	{
		new->cmd[i] = ft_strdup(token->token);
		i++;
		token = token->next;
	}
	set_flags(&new, shell);
	new->cmd[i] = NULL;
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
	return (1);
}
