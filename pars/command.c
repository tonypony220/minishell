#include "../minishell.h"

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
	/* rewrite for list */
	ft_lstiter(shell->cmd, print_process);

//	int i = 0;
//	int d = 0;
//	t_cmd *tmp;
//
//	tmp = shell->cmd;
//	while (tmp)
//	{
//		printf("cmd #%d >>> ", d);
//		while (tmp->cmd[i] != NULL)
//			printf("%s ", tmp->cmd[i++]);
//		printf("\n\tPIPE IN [%d] -- PIPE OUT [%d] -- PIPE NUMBER []\n", tmp->pipe[0], tmp->pipe[1]); //, tmp->_pipe);
//		tmp = tmp->next;
//		d++;

}

void	set_flags(struct process *new, t_shell *shell)
{
	//printf("=%d=%d\n", shell->flags.pipe_in, shell->flags.pipe_out);
//	new->_pipe = shell->flags.pipe_count;
	new->pipe[0] = shell->flags.pipe_in;
	new->pipe[1] = shell->flags.pipe_out;
	shell->flags.double_q = 0;
}


int	check_redir(t_token *token, int index, struct process **new, t_shell *shell)
{
	if (token->redir)
	{
		/* 1=>> 2=<< 3=< 4=> 0=NONE */
		shell->flags.redir_type == 1 && ((*new)->status |= A_FILE);
		shell->flags.redir_type == 2 && ((*new)->status |= HEREDOC);
		shell->flags.redir_type == 3 && ((*new)->status |= R_FILE);
		shell->flags.redir_type == 4 && 0;
		token->redir = 0;
		return (1);
	}
	return (0);
}

int		compose_command(t_list **cmds, t_token *token, t_shell *shell)
{
	struct	process	*new;
	int		i;
	int		size;

	i = 0;
	size = token_lstsize(token);
	if (token == NULL)
		return (-1);
	new = (struct process*)ft_calloc(1, sizeof(*new));
	if (new == NULL)
		return (-1);
	new->args = (char **)ft_calloc((size + 1), sizeof(char *));
	if (new->args == NULL)
		return (-1);
	new->shell = shell;
	new->env = shell->env;
	while (token)
	{
		if (check_redir(token, i, &new, shell)) /* NO FILE when << redirection */ 
			!(new->status & HEREDOC) && (new->file = ft_strdup(token->token));
		else
			new->args[i++] = ft_strdup(token->token);
		token = token->next;
	}
	set_flags(new, shell);
	ft_lstadd_back(cmds, ft_lstnew(new));
	return (1);
}
