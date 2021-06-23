#include "minishell.h"

/* func deprecated by ft_lst_find */
t_list					*get_dict_by_key(t_list *lst, void* (*f)(void *), char* key)
{
	while (lst)
	{
		//printf("%s %s\n", f(lst->content), key);
		if (!ft_strcmp(f(lst->content), key))
			return (lst);
		lst = lst->next;
	}
	return (0);
}

int						cmp_dict_keys(struct dict* content, struct dict* ref)
{
	return (ft_strcmp(content->key, ref->key));
}

void					del_dict(struct dict* content)
{
	free(content->value);
	free(content->key);
}

/* function not working */
//t_list					*del_dict_by_key(t_list *lst, void (*del)(void *),
//											void* (*f)(void *), char* key)
//{
//	t_list *one;
//	t_list *tmp;
//
//	one = get_dict_by_key(lst, f, key);
//	tmp = one->next;
//	//ft_lstdelone(one, del);
//	one = 0;
//	ft_lstlast(lst)->next = tmp;
//	return (0);
//}

void					*dict_key(struct dict* content)
{
	if (content)
		return (content->key);
	return (0);
}

/* like python set default */
int						dict_set_default(t_list *lst, char* key, char* value)
{
	t_list		*d;
	struct dict *dict;


	if ((d = get_dict_by_key(lst, dict_key, key)))
	{
		dict = d->content;
		free(dict->value);
		dict->value = ft_strdup(value);
	}
	else
	{
		dict = new_dict(ft_strdup(key), ft_strdup(value));
		d = ft_lstnew(dict);
		ft_lstadd_back(&lst, d);
	}
}


void					env_content_print(struct dict* content)
{
	printf("\t%s=%s\n", content->key, content->value);
}

struct dict			*new_dict(char *key, char *value)
{
	struct dict		*new;

	if ((new = malloc(sizeof(struct dict*))))
	{
		new->key = key;
		new->value = value;
	}
	return (new);
}

void					upload_env_to_dict(char **envp, t_list **env)
{
	t_list				*new;
	char				**key_value;
	struct dict			*content;

	while(*envp)
	{
		key_value = ft_split(*envp, '=');
		content = new_dict(key_value[0], key_value[1]);
		new = ft_lstnew(content);
		//new = lstnew_env(key_value[0], key_value[1]);
		ft_lstadd_back(env, new);
		//write(1, "HERE\n", 5);
		free(key_value);
		envp++;
	}
}
