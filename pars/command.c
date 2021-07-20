#include "../minishell.h"

void	print_command(t_shell *shell)
{
	ft_lstiter(shell->cmd, print_process);
}

void	set_flags(struct process *new, t_shell *shell)
{
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

int	check_redir(t_token *token, struct process **new, t_shell *shell)
{
	if (token->redir)
	{
		shell->in_compose = token->redir_type;
		if (token->redir_type == 2)
			heredoc_init(shell, token->token);
		if (token->redir_type == 1)
		{
			(*new)->status |= A_FILE;
			ft_lstadd_back(&(*new)->files_out,
				ft_lstnew(ft_strdup(token->token)));
		}
		if (token->redir_type == 3)
		{
			(*new)->status |= R_FILE;
			ft_lstadd_back(&(*new)->files_in,
				ft_lstnew(ft_strdup(token->token)));
		}
		if (token->redir_type == 4)
			ft_lstadd_back(&(*new)->files_out,
				ft_lstnew(ft_strdup(token->token)));
		shell->in_compose = 0;
		token->redir = 0;
		return (1);
	}
	return (0);
}

int	compose_command(t_list **cmds, t_token *token, t_shell *shell)
{
	struct process	*new;
	int				i;
	int				size;

	i = 0;
	if (token == NULL)
		return (1);
	size = token_lstsize(token);
	if (token->redir_type == 2)
		size = 1;
	new = (struct process *)ft_calloc(1, sizeof(*new));
	new->args = (char **)ft_calloc((size + 1), sizeof(char *));
	if (new == NULL || new->args == NULL)
		return (set_error(shell, -5));
	new->shell = shell;
	new->env = shell->env;
	while (token)
	{
		if (!check_redir(token, &new, shell))
			new->args[i++] = ft_strdup(token->token);
		token = token->next;
	}
	set_flags(new, shell);
	ft_lstadd_back(cmds, ft_lstnew(new));
	return (1);
}
