#include "minishell.h"

int	dict_add_back(t_list **env, struct s_dict *content)
{
	t_list				*new;

	new = ft_lstnew(content);
	if (!(new))
	{
		del_dict(content);
		return (0);
	}
	ft_lstadd_back(env, new);
	return (1);
}

/* note key and value strs are allocated */
int	upload_env_to_dict(char **envp, t_list **env)
{
	struct s_dict	*dict;
	char			**key_value;
	int				ret;

	ret = 1;
	while (*envp && ret)
	{
		key_value = split_env(*envp, '=');
		dict = new_dict(key_value[0], key_value[1]);
		if (!(dict))
			return (0);
		ret = dict_add_back(env, dict);
		free(key_value);
		envp++;
	}
	return (ret);
}

void	env_dict_print(void *d)
{
	struct s_dict	*content;

	content = (struct s_dict *)d;
	printf("declare -x %s=%s\n", content->key, content->value);
}

/* content of dict should not be freed 
 * 0 return should be handled in calling func 
 * */
char	*env_pull_to_str(struct s_dict *content)
{
	return (ft_strjoind(content->key, content->value, "="));
}

char	**split_env(char *str, char c)
{
	char	**ret;
	int		i;

	i = 0;
	ret = (char **)ft_calloc(3, sizeof(char **));
	if (ret == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			ret[0] = ft_substr(str, 0, i);
			if (ret[0] == NULL)
				return (NULL);
			ret[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
			if (ret[1] == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	return (ret);
}
