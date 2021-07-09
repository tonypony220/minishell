#include "../minishell.h"

void	single_quote(char *line, int i, t_shell *shell)
{
	int j;

	j = i;
	while(line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			shell->sq_err = 1;
			i++;
			while (line[i] != '\0')
			{
				if (line[i] == '\'')
				{
					shell->sq_err = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (shell->sq_err == 1)
		error_out(shell, "syntax error single quotes");
}

void	double_quote(char *line, int i, t_shell *shell)
{
	int j;

	while(line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			shell->dq_err = 1;
			i++;
			j = i;
			while (line[i] != '\0')
			{
				if (line[i] == '\"')
				{
					shell->dq_err = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (shell->dq_err == 1 && shell->sq_err == 0)
		error_out(shell, "syntax error double quotes");
}

void	pipe_syntax(char *line, int i, t_shell *shell)
{
	int j;

	j = shell->i;
	while(line[shell->i] != '\0')
	{
		if (line[shell->i] == '\"')
		{
			shell->i++;
			while (line[shell->i] != '\"')
				shell->i++;
		}
		if (line[shell->i] == '\'')
		{
			shell->i++;
			while (line[shell->i] != '\'')
				shell->i++;
		}
		if (line[shell->i] == '|')
		{
			space_skip(line, shell);
		}
	}
	if (shell->dq_err == 1 && shell->sq_err == 0)
		error_out(shell, "syntax error double quotes");
}

int		check_cmd(char *line, t_shell *shell)
{
	int j;
	char qq;

	j = shell->i;
	single_quote(line, j, shell);
	double_quote(line, j, shell);
	//pipe_syntax(line, j, shell);
	shell->dq_err = 0;
	shell->sq_err = 0;
	shell->i = j;
	if (shell->err == -1)
		return (-1);
	return (1);
}

int	pre_env_check(char *line, t_shell *shell)
{
	int i;
	int end;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			end = i;
			i++;
			while (line[i] != ' ' && line[i] != '\'' && line[i] != '\"'
					&& line[i] != '\\' && line[i] != '$')
					i++;
			if (get_env(shell, line, end + 1, i - 1) == 0)
			{
				shell->env_sign = 0;
				free_env_shell(shell);
				return (0);
			}
			else
				return (1);
		}
		(i)++;
	}
	return (0);
}

int	check_for_env(char **line, t_shell *shell)
{
	int i;

	i = 0;
	shell->env_sign = 0;
	if (line[0][i + 1] == '\0' || shell->flags.double_q == 0) // SegFault with single $
		return (0);
	while (line[0][i] != '\0')
	{
		if (line[0][i] == '$')
		{
			shell->env_sign = 1;
/* 			if (pre_env_check(line[0], shell) == 0)
				return (0); */
			*line = add_env_to_str(line[0], shell);
		}
		i++;
	}
	if (shell->env_sign)
		check_for_env(line, shell);
	return (0);
}

char	*add_env_to_str(char *line, t_shell *shell)
{
	char *tmp;
	char *tmp2;
	char *env;
	int i;
	int end;

	i = 0;
	env = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			end = i++;
			tmp = ft_substr(line, 0, end);
			while (ft_strchr(" \'\"\\$;:|", line[i]) == 0)
					i++;
			tmp2 = ft_substr(line, i, ft_strlen(line) - i);
			if (get_env(shell, line, end + 1, i - 1) == 1)
				env = ft_strdup(shell->env_value);
			free_env_shell(shell);
			tmp = ft_strjoin(tmp, env);
			tmp = ft_strjoin(tmp, tmp2);
			free(env);
			free(tmp2);
			free(line);
			return (tmp);
		}
		(i)++;
	}
	return (line);
}

void	check_for_pipe(char *line, t_shell *shell, t_token *token)
{
	int i;

	i = shell->i;
	shell->i++;
	space_skip(line, shell);
	if (line[shell->i] == '\0')
		shell->flags.pipe_out = -1;
	if (line[shell->i] == '|')
	{
		shell->flags.pipe_out++;
		compose_command(shell->cmd, token, shell);
	}
	shell->i = i;
}

void	main_parser(char *line, t_shell *shell, t_token **token)
{
	while(line[shell->i] != '\0')
	{
		if (line[shell->i] == '\'')
			parse_single_quotes(line, shell);
		else if (line[shell->i] == '\"')
			parse_double_quotes(line, shell);
		else if (line[shell->i] == '$')
			parse_env_sign(line, shell);
/* 		else if (line[shell->i] == '>' || line[shell->i] == '<')
			parse_redirect(line, shell); */
		else if (line[shell->i] == '|')
			parse_pipe(line, shell);
		else
			parse_cmd(line, shell);
		if (line[shell->i + 1] == ' ' || line[shell->i + 1] == '\0')
		{
			token_lstadd(token, shell->_arg, shell);
			check_for_pipe(line, shell, *token);
			free(shell->_arg);
			shell->_arg = NULL;
		}
		shell->i++;
	}
	compose_command(shell->cmd, *token, shell);
}

/* main enters here */
int			pre_parser(char *line, t_shell *shell)
{
	t_token	*token;

	shell->cmd = NULL;
	shell->i = 0;
	token = NULL;
	space_skip(line, shell);
	if (line[shell->i] == '|')
		return (error_out(shell, "syntax error near unexpected token"));
	if (check_cmd(line, shell) < 1) //check for syntax errors
		return (-1);
	main_parser(line, shell, &token);
	token_lstclear(&token);
	if (shell->cmd == NULL)
		return (0);
	return (1);
}
