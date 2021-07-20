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
	struct s_dict		*dict;
	char			**key_value;
	int				ret;

	ret = 1;
	while (*envp && ret)
	{
		key_value = ft_split(*envp, '=');
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
