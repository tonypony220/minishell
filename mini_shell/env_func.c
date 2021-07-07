#include "mini_parser.h"

t_env	*ft_env_list(t_env **lst, char *line, int j, int end)
{
	t_env	*first;
	t_env	*new;
	int i;

	if (!line)
		return (NULL);
	if (!(new = (t_env*)malloc(sizeof(*new))))
		return (0);
	i = j;
	new->key = ft_substr(line, 0, j);
	new->value = ft_substr(line, j + 1, end - j);
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		first = *lst;
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = new;
		*lst = first;
	}
	return (new);
}

int		value_and_key(char *value, char *key, t_shell *shell)
{
	return (1);
}

void	ft_env_clear(t_env **list)
{
	t_env	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->key);
		(*list)->key = NULL;
		free((*list)->value);
		(*list)->value = NULL;
		free(*list);
		*list = NULL;
		(*list) = tmp;
	}
}

void	print_env(t_shell *shell)
{
	while (shell->env)
	{
		//printf("%s=%s\n", shell->env->key, shell->env->value);
		ft_putendl(shell->env->key, 0);
		ft_putendl("=", 0);
		ft_putendl(shell->env->value, 1);
		shell->env = shell->env->next;
	}
}

void	env_parser(char **envp, t_env **env)
{
	int		i = 0, j = 0, len;

	while(envp[i] != '\0')
	{
		while(envp[i][j] != '\0')
		{
			if (envp[i][j] == '=')
			{
				//env->len = ft_strlen(envp[i]);
				//printf("LOL\n");
				ft_env_list(env, envp[i], j, ft_strlen(envp[i]));
				j = 0;
				break ;
			}
			j++;
		}
		i++;
	}
}

void	init_env(char **envp, t_shell *shell)
{
	t_env	*env;

	env = NULL;
	env_parser(envp, &env);
	shell->env = env;
	//ft_env(shell);
	//ft_env_clear(&shell->env);
}

void	ft_env(t_shell *shell)
{
	print_env(shell);
}

/* char	*get_env(t_shell *shell, char *line, int i, int end)
{
	char *tmp;
	t_env *env_tmp;

	env_tmp = shell->env;
	tmp = ft_substr(line, i, end - i + 1);
	//ft_putendl(tmp, 1);
	while (shell->env)
	{
		if ((ft_strncmp(tmp, shell->env->key, ft_strlen(tmp)) == 0)
				&& (ft_strlen(tmp) == ft_strlen(env_tmp->key)))
		{
			free(tmp);
			//ft_putendl(shell->env->key, 0);
			//ft_putendl("=", 0);
			//ft_putendl(shell->env->value, 1);
			shell->env->len = ft_strlen(shell->env->value);
			return (shell->env->value);
		}
		shell->env = shell->env->next;
	}
	free(tmp);
	return (NULL);
} */

int	get_env(t_shell *shell, char *line, int i, int end)
{
	char *tmp;
	t_env *env_tmp;

	env_tmp = shell->env;
	tmp = ft_substr(line, i, end - i + 1);
	//ft_putendl(tmp, 1);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->key, ft_strlen(tmp) + 1) == 0))
		{
			free(tmp);
			shell->env_len = ft_strlen(env_tmp->value);
			shell->env_value = ft_strdup(env_tmp->value);
			//ft_env_clear(&env_tmp);
			return (1);
		}
		env_tmp = env_tmp->next;
	}
	free(tmp);
	//ft_env_clear(&env_tmp);
	return (0);
}

int		ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

int		check_env_syntax(char *line, int i)
{
	if (line[i] >= '0' && line[i] <= '9')
		return (-1);
	while(line[i] != '=')
	{
		if (!(ifkey(line[i])))
			return (-1);
		i++;
	}
	return (1);
}
