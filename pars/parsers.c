#include "../minishell.h"

int	parse_cmd(char *line, t_shell *shell)
{
	char *substr;

	shell->_arg = NULL;
	substr = NULL;
	space_skip(line, shell);
	shell->start = shell->i;
	if (ft_strchr("$\'\"><|", line[shell->i]))
	{
		(shell->i)--;
		return (1);
	}
	while (line[shell->i] != '\0')
	{
		if (ft_strchr(" \'\"", line[shell->i + 1]) || !line[shell->i + 1])
		{
			shell->end = shell->i;
			substr = ft_substr(line, shell->start, shell->end - shell->start + 1);
			shell->_arg = token_strjoin(shell->_arg, substr);
			free(substr);
			if (ft_strchr("$\'\"><|", line[shell->i]))
				(shell->i)--;
			return (1);
		}
		(shell->i)++;
	}
	return (1);
}

int	parse_double_quotes(char *line, t_shell *shell)
{
	char *substr;

	(shell->i)++;
	if (line[shell->i] == '\"')
		return (1);
	shell->start = shell->i;
	while (line[shell->i] != '\0')
	{
		if (line[shell->i + 1] == '\"')
		{
			shell->end = (shell->i);
			shell->flags.double_q = 1;
			substr = ft_substr(line, shell->start, shell->end - shell->start + 1);
			shell->_arg = token_strjoin(shell->_arg, substr);
			free(substr);
			shell->i++;
			return (1);
		}
		(shell->i)++;
	}
	return (1);
}

int	parse_single_quotes(char *line, t_shell *shell)
{
	char *substr;

	(shell->i)++;
	if (line[shell->i] == '\'')
		return (1);
	shell->start = shell->i;
	while (line[shell->i] != '\0')
	{
		if (line[shell->i + 1] == '\'')
		{
			shell->end = (shell->i);
			substr = ft_substr(line, shell->start, shell->end - shell->start + 1);
			shell->_arg = token_strjoin(shell->_arg, substr);
			free(substr);
			shell->i++;
			return (1);
		}
		(shell->i)++;
	}
	return (1);
}

void	free_env_shell(t_shell *shell)
{
	shell->env_len = 0;
	if (shell->env_value)
		free(shell->env_value);
	shell->env_value = NULL;
}

int	parse_env_sign(char *line, t_shell *shell)
{
	if (line[(shell->i) + 1] == ' ' || line[(shell->i) + 1] == '\0')
	{
		shell->_arg = ft_strdup("$");
		return (1);
	}
	(shell->i)++;
	shell->start = shell->i;
/* 	if (check_env_syntax(line, shell->start) < 0)
		return (-1); */
	while (line[shell->i] != '\0')
	{
		if (ft_strchr(" \'\"\\$><|", line[shell->i + 1]) || !line[shell->i + 1])
		{
			shell->end = shell->i; // " \'\"\\$\0"
			get_env(shell, line, shell->start, shell->end);
			shell->start = 0;
			shell->end = shell->env_len;
			shell->_arg = token_strjoin(shell->_arg, shell->env_value);
			free_env_shell(shell);
			if (ft_strchr("\'\"\\$><|", line[shell->i]))
				(shell->i)--;
			return (1);
		}
		(shell->i)++;
	}
	return (1);
}

int	parse_redirect(char *line, t_token **token, t_shell *shell)
{
	shell->flags.has_redir = 1;
	if (line[shell->i + 1] == '>')
	{
		shell->flags.double_redir = 1;
		shell->i += 2;
	}
	else if (line[shell->i + 1] == '<')
	{
		shell->flags.double_out = 1;
		shell->i += 2;
	}
	else if (line[shell->i] == '<')
	{
		shell->flags.out = 1;
		shell->i++;
	}
	else
	{
		shell->flags.red = 1;
		shell->i++;
	}
	(*token)->redir = 1;
	return (0);
}

int	parse_pipe(char *line, t_shell *shell)
{
	shell->flags.has_pipe = 1;
	shell->flags.pipe_count++;
	shell->flags.pipe_in = shell->flags.pipe_out;
	return (1);
}