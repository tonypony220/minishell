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

int						cmp_dict_keys(void* content, void* ref)
{
	return (ft_strcmp(
			((struct dict*)content)->key, ((struct dict*)ref)->key));
}

void					del_dict(void *content)
{
	struct dict *d;

	d = (struct dict*)content;
//	printf(">>>%s>%s\n", d->key, d->value);
	free(d->value);
	free(d->key);
	free(d);
}


char					*dict_key(void* data)
{
	struct dict *content;

	content = (struct dict*)data;
	if (content)
		return (content->key);
	return (0);
}


char					*dict_value(void* data)
{
	struct dict *content;

	content = (struct dict*)data;
	if (content)
		return (content->value);
	return (0);
}
/* like python set default 
 * function expects to recive allocated key and value
 */
int						dict_set_default(t_list *lst, char* key, char* value)
{
	struct dict *d;

	if (!(d = new_dict(key, value)))
	{
		free(key);
		free(value);
		return (0);
	}
	ft_lst_rm(&lst, d, cmp_dict_keys, del_dict);
	return (dict_add_back(&lst, d));

	//t_list		*one;
	//struct dict *dict;

	//dict = new_dict("BO", );
	//one = ft_lst_find(env_lst, (dict = ), cmp_dict_keys);

	//if ((one = get_dict_by_key(lst, dict_key, key)))
	//{
	//	dict = d->content;
	//	free(dict->value);
	//	free(key);
	//	dict->value = ft_strdup(value);
	//}
	//else
	//{
	//	dict = new_dict(ft_strdup(key), ft_strdup(value));
	//	one = ft_lstnew(dict);
	//	ft_lstadd_back(&lst, d);
	//}
}

void					dict_print(void* d)
{
	struct dict* content;

	content = d;
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

