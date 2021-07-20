#include "../minishell.h"

int	check_for_env(char **line, t_shell *shell)
{
	int	i;

	i = 0;
	shell->env_sign = 0;
	if (line[0][i + 1] == '\0' || shell->flags.double_q == 0)
		return (0);
	while (line[0][i] != '\0')
	{
		if (line[0][i] == '$')
		{
			shell->env_sign = 1;
			if (line[0][i + 1] == '?')
				shell->_env_exit = 1;
			*line = add_env_to_str(line[0], shell);
		}
		i++;
	}
	if (shell->env_sign)
		check_for_env(line, shell);
	return (0);
}

static void	join_and_free(char **tmp, char *env, char *tmp2, char *line)
{
	*tmp = token_strjoin(*tmp, env);
	*tmp = token_strjoin(*tmp, tmp2);
	if (env)
		free(env);
	if (tmp2)
		free(tmp2);
	if (line)
		free(line);
}

char	*add_env_to_str(char *line, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;
	char	*env;
	int		i;
	int		end;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '$')
		{
			end = i++;
			tmp = ft_substr(line, 0, end);
			while (ft_isalnum(line[i]) || line[i] == '_')
				i++;
			tmp2 = ft_substr(line, i, ft_strlen(line) - i);
			if (get_env(shell, line, end + 1, i - 1) == 1)
				env = ft_strdup(shell->env_value);
			free_env_shell(shell);
			join_and_free(&tmp, env, tmp2, line);
			return (tmp);
		}
	}
	return (line);
}

void	join_env_string(t_shell *shell, char *line)
{
	shell->end = shell->i;
	get_env(shell, line, shell->st, shell->end);
	shell->st = 0;
	shell->end = shell->env_len;
	shell->_arg = token_strjoin(shell->_arg, shell->env_value);
	free_env_shell(shell);
}
