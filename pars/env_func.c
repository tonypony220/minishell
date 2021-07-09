#include "../minishell.h"

void	ft_env(t_shell *shell)
{
	ft_lstiter(shell->env, dict_print);	
}

int	get_env(t_shell *shell, char *line, int i, int end)
{
	/* function stores found values in shell structure */		
	t_list *one;
	struct dict *d;
	char *key;
	int	ret; 

	ret = 0;
	key = ft_substr(line, i, end - i + 1); // no check for malloc failure
	one = ft_lst_find(shell->env, (d = new_dict(key, 0)), cmp_dict_keys); // mo malloc dict check also
	if (one)
	{
		shell->env_len = ft_strlen(dict_value(one->content));
		shell->env_value = ft_strdup(dict_value(one->content));  // can't use direct pointer from dict content
		ret = 1;
	}
	free(key);
	//free(one);
	return (ret);
	
/// ......TO BE SUBSTITUTED CODE	.........
/* 	char *key;
	t_list *env_tmp;

	env_tmp = shell->env;
	key = ft_substr(line, i, end - i + 1);
	//ft_putendl(tmp, 1);
	while (env_tmp)
	{
		if ((ft_strncmp(key, env_tmp->key, ft_strlen(key) + 1) == 0))
		{
			free(key);
			shell->env_len = ft_strlen(env_tmp->value);
			shell->env_value = ft_strdup(env_tmp->value);
			//ft_env_clear(&env_tmp);
			return (1);
		}
		env_tmp = env_tmp->next;
	}
	free(key);
	//ft_env_clear(&env_tmp);
	return (0); */
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
