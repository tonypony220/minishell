#include "../minishell.h"

int	get_env(t_shell *shell, char *line, int i, int end)
{		
	t_list			*one;
	struct s_dict	*d;
	char			*key;

	if (shell->_env_exit)
	{
		shell->env_value = ft_itoa(shell->last_exit_code);
		return (1);
	}
	key = ft_substr(line, i, end - i + 1);
	one = ft_lst_find(shell->env, (d = new_dict(key, 0)),
			cmp_dict_keys);
	if (one)
	{
		shell->env_len = ft_strlen(dict_value(one->content));
		shell->env_value = ft_strdup(dict_value(one->content));
	}
	else
		shell->env_value = ft_strdup("");
	free(key);
	free(d);
	return (1);
}

void	free_env_shell(t_shell *shell)
{
	shell->env_len = 0;
	if (shell->env_value)
		free(shell->env_value);
	shell->env_value = NULL;
}

int	parse_env_sign(char *st, t_shell *shell)
{
	if (!ft_isalnum(st[(shell->i) + 1]) && !ft_strchr("_?", st[(shell->i) + 1]))
	{
		shell->_arg = token_strjoin(shell->_arg, "$");
		return (1);
	}
	shell->st = ++shell->i;
	if (st[shell->i] == '?')
		shell->_env_exit = 1;
	if (ft_isdigit(st[shell->i]))
	{
		shell->_arg = ft_strdup("");
		return (1);
	}
	while (st[shell->i] != '\0')
	{
		if (ft_strchr(" \'\"\\$><|=![].,?@#%%^&*()=+|/:;'\0", st[shell->i + 1]))
		{
			join_env_string(shell, st);
			if (ft_strchr("\'\"\\$><|", st[shell->i]))
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
	if ((line[i] >= '0' && line[i] <= '9') || line[i] == '=')
		return (-1);
	while (line[i] != '=')
	{
		if (!(ifkey(line[i])))
			return (-1);
		i++;
	}
	return (1);
}
