#include "minishell.h"

struct s_dict	*new_dict(char *key, char *value)
{
	struct s_dict		*new;

	new = malloc(sizeof(struct s_dict));
	if ((new))
	{
		new->key = key;
		new->value = value;
	}
	return (new);
}

char	*dict_value(void *data)
{
	struct s_dict	*content;

	content = (struct s_dict *)data;
	if (content)
		return (content->value);
	return (0);
}

/* like python set default 
 * function expects to recive allocated key and value
 */
int	dict_set_default(t_list *lst, char *key, char *value)
{
	struct s_dict	*d;

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
	struct s_dict	*content;

	content = d;
	printf("%s=%s\n", content->key, content->value);
}
