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
	while(line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] != '\"')
				i++;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		if (line[i] == '|')
		{
			i++;	
			i = space_skip(line, i);
			if (line[i] == '\0' || ft_strchr("|><", line[i]))
				shell->pipe_err = 1;
		}
		i++;
	}
	if (shell->pipe_err == 1 && shell->dq_err == 0)
		error_out(shell, "syntax error near unexpected token '|'");
}

void	redir_syntax(char *line, int i, t_shell *shell)
{
	while(line[i] != '\0')
	{
		if (line[i] == '\"')
			while (line[++i] != '\"')
				;
		if (line[i] == '\'')
			while (line[++i] != '\'')
				;
		if (ft_strchr("><", line[i]))
		{
			i++;
			if (ft_strchr("|><", line[i]))
				i++;
			i = space_skip(line, i);
			if (line[i] == '\0' || ft_strchr("|><", line[i]))
				shell->redir_err = 1;
		}
		i++;
	}
	if (shell->redir_err == 1 && shell->pipe_err == 0)
		error_out(shell, "syntax error near unexpected token 'newline'");
}
