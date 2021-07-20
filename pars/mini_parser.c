#include "../minishell.h"

int	check_cmd(char *line, t_shell *shell)
{
	int		j;
	char	qq;

	j = shell->i;
	single_quote(line, j, shell);
	double_quote(line, j, shell);
	pipe_syntax(line, j, shell);
	redir_syntax(line, j, shell);
	shell->dq_err = 0;
	shell->sq_err = 0;
	shell->pipe_err = 0;
	shell->redir_err = 0;
	if (shell->err < 0)
		return (-1);
	return (1);
}

void	check_for_pipe(char *line, t_shell *shell, t_token **token)
{
	int	i;

	i = shell->i;
	if (line[shell->i] == ' ')
		return ;
	shell->i++;
	shell->i = space_skip(line, shell->i);
	if (line[shell->i] == '\0')
		shell->flags.pipe_out = -1;
	if (line[shell->i] == '|')
	{
		shell->flags.pipe_out++;
		compose_command(&shell->cmd, *token, shell);
		token_lstclear(token);
	}
	shell->i = i;
}

void	main_parser(char *line, t_shell *shell, t_token **token)
{
	while (line[shell->i] != '\0')
	{
		if (line[shell->i] == '\'')
			parse_single_quotes(line, shell);
		else if (line[shell->i] == '\"')
			parse_double_quotes(line, shell);
		else if (line[shell->i] == '$')
			parse_env_sign(line, shell);
		else if (line[shell->i] == '>' || line[shell->i] == '<')
			parse_redirect(line, shell);
		else if (line[shell->i] == '|')
			parse_pipe(line, shell);
		else
			parse_cmd(line, shell);
		if (ft_strchr(" ><|", line[shell->i + 1]) || !line[shell->i + 1])
		{
			token_lstadd(token, shell->_arg, shell);
			check_for_pipe(line, shell, token);
			free(shell->_arg);
			shell->_arg = NULL;
		}
		shell->i++;
	}
	compose_command(&shell->cmd, *token, shell);
}

/* main enters here */
int	pre_parser(char *line, t_shell *shell)
{
	t_token	*token;

	shell->i = 0;
	token = NULL;
	shell->i = space_skip(line, shell->i);
	shell->_env_exit = 0;
	shell->redir_count = 0;
	if (line[shell->i] == '|')
		set_error(shell, -3);
	check_cmd(line, shell);
	main_parser(line, shell, &token);
	token_lstclear(&token);
	error_out(shell);
	if (shell->cmd == NULL)
		return (0);
	return (1);
}
