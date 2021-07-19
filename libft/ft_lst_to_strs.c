#include "libft.h"

/* todo malloc fail */
char	**ft_lst_to_strs(t_list *lst, char *(*pull_str)())
{
	char				**env;
	char				**tmp_env;
	int					size;

	size = ft_lstsize(lst);
	env = ft_calloc((size + 1) * sizeof(env), 1);
	if (!env)
		return (0);
	tmp_env = env;
	while (lst)
	{
		*env = pull_str(lst->content);
		env++;
		lst = lst->next;
	}
	return (tmp_env);
}
