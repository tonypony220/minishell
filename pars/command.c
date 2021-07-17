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
		if (token->redir_type == 2)
			heredoc_comp(shell, token->token);
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
//	printf("len list %d\n", ft_lstsize(new->files_out));
//	ft_lstiter(new->files_out, pr);
//
//	char* filename;
//	//filename = ft_lstgen(new->files_out, get_filename);
//	while ((filename = ft_lstgen(new->files_out, get_filename)) && i < 10)
//	{
//		printf("> > > >%s %d\n", filename, i++);
//		//filename = ft_lstgen(new->files_out, get_filename);
//	}
//	while ((filename = ft_lstgen(new->files_out, get_filename)) && i < 10)
//	{
//		printf("> > > >%s %d\n", filename, i++);
//		//filename = ft_lstgen(new->files_out, get_filename);
//	}

	set_flags(new, shell);
	ft_lstadd_back(cmds, ft_lstnew(new));
	return (1);
}








