#include "../minishell.h"

int	get_env(t_shell *shell, char *line, int i, int end)
{		
	t_list		*one;
	struct dict	*d;
	char		*key;
	int			ret;

	if (shell->_env_exit)
	{
		shell->env_value = ft_itoa(shell->last_exit_code);
		return (1);
	}
	ret = 0;
	key = ft_substr(line, i, end - i + 1);// no check for malloc failure
	one = ft_lst_find(shell->env, (d = new_dict(key, 0)),
			cmp_dict_keys);// mo malloc dict check also
	if (one)
	{
		shell->env_len = ft_strlen(dict_value(one->content));
		shell->env_value = ft_strdup(dict_value(one->content));
		ret = 1;
	}
	free(key);
	return (ret);
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
	shell->st = ++shell->i;
	if (line[shell->i] == '?')
		shell->_env_exit = 1;
	while (line[shell->i] != '\0')
	{
		if (ft_strchr(" \'\"\\$><|", line[shell->i + 1]) || !line[shell->i + 1])
		{
			shell->end = shell->i;
			get_env(shell, line, shell->st, shell->end);
			shell->st = 0;
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

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

int	check_env_syntax(char *line, int i)
{
	if (line[i] >= '0' && line[i] <= '9')
		return (-1);
	while (line[i] != '=')
	{
		if (!(ifkey(line[i])))
			return (-1);
		i++;
	}
	return (1);
}
