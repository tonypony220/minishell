#include "minishell.h"

int					dict_add_back(t_list **env, struct dict *content) //char *key, char *value)
{
	t_list				*new;

	if (!(new = ft_lstnew(content)))
	{
		del_dict(content);
		return (0);
	}
	ft_lstadd_back(env, new);
	return (1);
}

/* note key and value strs are allocated */
int					upload_env_to_dict(char **envp, t_list **env)
{
	struct dict *dict;
	int ret;

	ret = 1;
	while(*envp && ret)
	{
		key_value = ft_split(*envp, '=');
		if (!(dict = new_dict(key, value)));
			return (0);
		ret = dict_add_back(env, dict);
		free(key_value);
		envp++;
	}
	return (ret);
}


void					env_dict_print(struct dict* content)
{
	printf("declare -x %s=%s\n", content->key, content->value);
}

/* content of dict should not be freed 
 * 0 return should be handled in calling func 
 * */
char					*env_pull_to_str(struct dict* content)
{
	return (ft_strjoind(content->key, content->value, "="));
}

//char					**download_env_to_strs(t_list *lst)
//{
//	char				**env;
//	char				**tmp_env;
//	int					size;
//
//	size = ft_lstsize(lst);
//	if (!(env = ft_calloc(size * sizeof(env))
//		return (0);
//	tmp_env = env;
//	while (lst)
//	{
//		*env = dict_to_str(lst->content, "="); // todo malloc fail
//		env++;
//		lst = lst->next;
//	}
//	return (tmp_env);
//}
