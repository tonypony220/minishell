#include "../minishell.h"

int	parse_cmd(char *line, t_shell *shell)
{
	char	*substr;

	substr = NULL;
	shell->i = space_skip(line, shell->i);
	shell->st = shell->i;
	if (ft_strchr("$\'\"><|", line[shell->i]))
	{
		(shell->i)--;
		return (1);
	}
	while (line[shell->i] != '\0')
	{
		if (ft_strchr(" \'\"><|$", line[shell->i + 1]) || !line[shell->i + 1])
		{
			shell->end = shell->i;
			substr = ft_substr(line, shell->st, shell->end - shell->st + 1);
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
	char	*substr;

	(shell->i)++;
	if (line[shell->i] == '\"')
		return (1);
	shell->st = shell->i;
	while (line[shell->i] != '\0')
	{
		if (line[shell->i + 1] == '\"')
		{
			shell->end = (shell->i);
			shell->flags.double_q = 1;
			substr = ft_substr(line, shell->st, shell->end - shell->st + 1);
			check_for_env(&substr, shell);
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
	char	*substr;

	(shell->i)++;
	if (line[shell->i] == '\'')
		return (1);
	shell->st = shell->i;
	while (line[shell->i] != '\0')
	{
		if (line[shell->i + 1] == '\'')
		{
			shell->end = (shell->i);
			substr = ft_substr(line, shell->st, shell->end - shell->st + 1);
			shell->_arg = token_strjoin(shell->_arg, substr);
			free(substr);
			shell->i++;
			return (1);
		}
		(shell->i)++;
	}
	return (1);
}

int	parse_redirect(char *line, t_shell *shell)
{
	shell->flags.has_redir = 1;
	if (line[shell->i + 1] == '>')
	{
		shell->flags.redir_type = 1;
		shell->i += 2;
	}
	else if (line[shell->i + 1] == '<')
	{
		shell->flags.redir_type = 2;
		shell->i += 2;
	}
	else if (line[shell->i] == '<')
	{
		shell->flags.redir_type = 3;
		shell->i++;
	}
	else
	{
		shell->flags.redir_type = 4;
		shell->i++;
	}
	if (line[shell->i] != ' ' && line[shell->i] != '|')
		shell->i--;
	return (0);
}

int	parse_pipe(char *line, t_shell *shell)
{
	shell->flags.has_pipe = 1;
	shell->flags.pipe_in = shell->flags.pipe_out;
	return (1);
}
