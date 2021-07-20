#include "minishell.h"

struct dict	*new_dict(char *key, char *value)
{
	struct dict		*new;

	new = malloc(sizeof(struct dict));
	if ((new))
	{
		new->key = key;
		new->value = value;
	}
	return (new);
}

char	*dict_value(void *data)
{
	struct dict	*content;

	content = (struct dict *)data;
	if (content)
		return (content->value);
	return (0);
}

/* like python set default 
 * function expects to recive allocated key and value
 */
int	dict_set_default(t_list *lst, char *key, char *value)
{
	struct dict	*d;

	d = new_dict(key, value);
	if (!(d))
	{
		free(key);
		free(value);
		return (0);
	}
	ft_lst_rm(&lst, d, cmp_dict_keys, del_dict);
	return (dict_add_back(&lst, d));
}

void	dict_print(void *d)
{
	struct dict	*content;

	content = d;
	printf("%s=%s\n", content->key, content->value);
}
