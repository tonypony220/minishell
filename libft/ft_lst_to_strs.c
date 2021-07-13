#include "libft.h"

char					**ft_lst_to_strs(t_list *lst, char* (*pull_str)())
{
	char				**env;
	char				**tmp_env;
	int					size;

	size = ft_lstsize(lst);
	if (!(env = ft_calloc((size + 1) * sizeof(env), 1)))
		return (0);
	tmp_env = env;
	while (lst)
	{
		*env = pull_str(lst->content); // todo malloc fail
		env++;
		lst = lst->next;
	}
	return (tmp_env);
}
