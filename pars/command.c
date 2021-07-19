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
		shell->in_compose = token->redir_type;
		if (token->redir_type == 2)
			heredoc_init(shell, token->token);
		if (token->redir_type == 1 && ((*new)->status |= A_FILE)) 
			ft_lstadd_back(&(*new)->files_out, ft_lstnew(ft_strdup(token->token)));
		if (token->redir_type == 3 && ((*new)->status |= R_FILE))
			ft_lstadd_back(&(*new)->files_in, ft_lstnew(ft_strdup(token->token)));
		if (token->redir_type == 4) 
			ft_lstadd_back(&(*new)->files_out, ft_lstnew(ft_strdup(token->token)));
		//print_token(shell->files);
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
		//print_token(token);
		//printf("token=[%s]\nredir=[%d]\n", token->token, token->redir_type);
		if (!check_redir(token, i, &new, shell)) // == 2
			new->args[i++] = ft_strdup(token->token);
		//printf("TESTING %d=[%s]\n", i, new->args[i]);
		token = token->next;
	}
	i = 0;
	set_flags(new, shell);
	ft_lstadd_back(cmds, ft_lstnew(new));
	return (1);
}








