#include "../minishell.h"

void	print_command(t_shell *shell)
{
	/* rewrite for list */
	ft_lstiter(shell->cmd, print_process);
}

void	set_flags(struct process *new, t_shell *shell)
{
	//printf("=%d=%d\n", shell->flags.pipe_in, shell->flags.pipe_out);
	//	new->_pipe = shell->flags.pipe_count;
	//printf("PIPE COUNT=[%d]\n", shell->flags.pipe_count);

	new->pipe[0] = shell->flags.pipe_in;
	if (shell->flags.pipe_count)
		new->pipe[1] = shell->flags.pipe_out;
	else
		new->pipe[1] = -1;
	if (shell->flags.heredoc)
	{
		shell->flags.pipe_in = shell->flags.pipe_out;
		shell->flags.heredoc = 0;
	}
	shell->flags.pipe_count--;
	shell->flags.double_q = 0;
}

int	check_redir(t_token *token, int index, struct process **new, t_shell *shell)
{
	char *name;

	if (token->redir)
	{
		/* 1=>> 2=<< 3=< 4=> 0=NONE */
		//printf("%d redir type\n", token->redir_type);
/* 		token->redir_type == 1 && ((*new)->status |= A_FILE) && ((*new)->file[OUT] = ft_strdup(token->token));
		token->redir_type == 2 && heredoc_comp(shell, token->token);
		token->redir_type == 3 && ((*new)->status |= R_FILE) && ((*new)->file[IN] = ft_strdup(token->token));
		token->redir_type == 4 && ((*new)->file[OUT] = ft_strdup(token->token)); */
		
		/* FILE NAMES LIST == shell->files */
		shell->in_compose = token->redir_type;
		token->redir_type == 1 && ((*new)->status |= A_FILE) && (name = ft_strdup(token->token));
		token->redir_type == 2 && heredoc_comp(shell, token->token);
		token->redir_type == 3 && ((*new)->status |= R_FILE) && (name = ft_strdup(token->token));
		token->redir_type == 4 && (name = ft_strdup(token->token));
		token_lstadd(&shell->files, name, shell);
		free(name);

		printf("%p << files list \n", shell->files);
		print_token(shell->files);

		shell->in_compose = 0;
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
	if (token == NULL)
		return (1);
	size = token_lstsize(token); //token->redir_type == 2 ||
	if (token->redir_type == 2)
		size = 1;
	if (!(new = (struct process*)ft_calloc(1, sizeof(*new)))
	|| !(new->args = (char **)ft_calloc((size + 1), sizeof(char *)))) 
		return (-1);
	new->shell = shell;
	new->env = shell->env;
	while (token)
	{
		//printf("%d '%s' token redir_type=%d\n", size, token->token, token->redir_type);
// rewrite this 
			//!(new->status & HEREDOC) && (new->file = ft_strdup(token->token));
		if (!check_redir(token, i, &new, shell)) // == 2
			new->args[i++] = ft_strdup(token->token);
		token = token->next;
	}
	set_flags(new, shell);
	ft_lstadd_back(cmds, ft_lstnew(new));
	return (1);
}
