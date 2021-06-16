#include "mini_parser.h"

int	parse_cmd(char *line, t_list **cmd, t_shell *shell)
{
	space_skip(line, shell);
	shell->start = shell->i;
	if (line[shell->i] == '\'' || line[shell->i] == '\"' || line[shell->i] == '\\'
			|| line[shell->i] == '$')
	{
		(shell->i)--;
		return (1);
	}	
	//printf("%s\n", line);
	//printf("[%c]\n", line[shell->start]);
	while (line[shell->i] != '\0')
	{
		if (line[shell->i] == ' ' || line[shell->i + 1] == '\0' || line[shell->i] == '\'' 
				|| line[shell->i] == '\"' || line[shell->i] == '\\')
		{
			space_skip(line, shell);
			shell->end = shell->i;
			if (line[shell->i + 1] == '\0')
				shell->end++;
			//ft_putshell->endl("YA TYT", 1);
			//printf("[%c-%c]\n", line[shell->start], line[shell->end]);
			ft_lstadd(cmd, line, shell);
			if (line[shell->i] == '\'' || line[shell->i] == '\"' || line[shell->i] == '\\'
					|| line[shell->i] == '$')
			{
				(shell->i)--;
				return (1);
			}
			shell->start = shell->end++;
		}
		(shell->i)++;
	}
	return (1);
}

int	parse_double_quotes(char *line, t_list **cmd, t_shell *shell)
{
	(shell->i)++;
	shell->start = shell->i;
/* 	check_for_env(shell, line, shell->start);
	while (shell->env_sign)
		add_env_to_str(&line, shell, shell->start); */
	while (line[shell->i] != '\0')
	{
		if (line[shell->i] == '\"')
		{
			shell->end = (shell->i)++;
			if (line[shell->i] == '\"' || line[shell->i] == '\'')
				(shell->i) = shell->end;
			//ft_putshell->endl("\"", 1);
			//printf("[%c - %c]\n", line[shell->start], line[shell->end]);
			ft_lstadd(cmd, line, shell);
			return (1);
		}
		(shell->i)++;
	}
	return (1);
}

int	parse_single_quotes(char *line, t_list **cmd, t_shell *shell)
{
	(shell->i)++;
	shell->start = shell->i;
	while (line[shell->i] != '\0')
	{
		if (line[shell->i] == '\'')
		{
			shell->end = (shell->i)++;
			if (line[shell->i] == '\"' || line[shell->i] == '\'')
				(shell->i) = shell->end;
			//ft_putshell->endl("\'", 1);
			//printf("[%c - %c]\n", line[shell->start], line[shell->end]);
			ft_lstadd(cmd, line, shell);
			return (1);
		}
		(shell->i)++;
	}
	return (1);
}

int	parse_env_sign(char *line, t_list **cmd, t_shell *shell)
{
	if (line[(shell->i) + 1] == ' ' || line[(shell->i) + 1] == '\0')
	{
		shell->start = shell->i;
		shell->end = shell->i + 1;
		ft_lstadd(cmd, line, shell);
		return (1);
	}
	(shell->i)++;
	shell->start = shell->i;
/* 	if (check_env_syntax(line, shell->start) < 0)
		return (-1); */
	while (line[shell->i] != '\0')
	{
		if (line[shell->i + 1] == ' ' || line[shell->i + 1] == '\0' || line[shell->i + 1] == '\'' 
				|| line[shell->i + 1] == '\"' || line[shell->i + 1] == '\\' || line[shell->i + 1] == '$')
		{
			shell->end = shell->i;
			get_env(shell, line, shell->start, shell->end);
			shell->start = 0;
			shell->end = shell->env_len;
			ft_lstadd(cmd, shell->env_value, shell);
			free(shell->env_value);
			(shell->i)++;
			if (line[shell->i] == '\'' || line[shell->i] == '\"' || line[shell->i] == '\\'
					|| line[shell->i] == '$')
				(shell->i)--;
			return (1);
		}
		(shell->i)++;
	}
	return (1);
}
