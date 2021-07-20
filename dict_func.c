#include "minishell.h"

/* func deprecated by ft_lst_find */
t_list	*get_dict_by_key(t_list *lst, void *(*f)(void *), char *key)
{
	while (lst)
	{
		if (!ft_strcmp(f(lst->content), key))
			return (lst);
		lst = lst->next;
	}
	return (0);
}

int	cmp_dict_keys(void *content, void *ref)
{
	return (ft_strcmp(
			((struct s_dict*)content)->key,
			((struct s_dict*)ref)->key));
}

void	del_dict(void *content)
{
	struct s_dict	*d;

	d = (struct s_dict *)content;
	free(d->value);
	free(d->key);
	free(d);
}

char	*dict_key(void *data)
{
	struct s_dict	*content;

	content = (struct s_dict *)data;
	if (content)
		return (content->key);
	return (0);
}

char	*dict_to_str(void *data)
{
	struct s_dict	*content;

	content = (struct s_dict *)data;
	if (content)
		return (ft_strjoind(content->key, content->value, "="));
	return (0);
}
