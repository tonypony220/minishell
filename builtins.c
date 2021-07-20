#include "minishell.h"

int	msh_echo(struct s_process *ps)
{
	int				i;
	int				virgin;

	i = 1;
	virgin = 0;
	!ft_strcmp(ps->args[1], "-n") && (i = 2);
	while (ps->args[i])
	{
		virgin && printf(" ");
		printf("%s", ps->args[i]);
		virgin++;
		i++;
	}
	!ft_strcmp(ps->args[1], "-n") || printf("\n");
	return (1);
}

int	export_ps_args(struct s_process *ps)
{
	int		i;
	int		ret;
	char	**key_value;

	i = 0;
	while (ps->args[++i])
	{
		if (check_env_syntax(ps->args[i], 0) == 1)
		{
			key_value = ft_split(ps->args[i], '=');
			if (!(key_value))
				return (0);
			ret = dict_set_default(ps->env, key_value[0], key_value[1]);
			free(key_value);
		}
		else
			printf(SHELL_NAME": '%s': %s\n",
				ps->args[i], "not a valid identifier");
	}
	return (ret);
}

int	msh_export(struct s_process *ps)
{
	int				ret;

	ret = 1;
	if (ps->args[1])
		ret = export_ps_args(ps);
	else
	{
		ft_lst_sort_bubble(&ps->env, cmp_dict_keys);
		ft_lstiter(ps->env, env_dict_print);
	}
	return (ret);
}

int	msh_unset(struct s_process *ps)
{
	struct s_dict	*d;
	int			i;

	i = 0;
	while (ps->args[++i])
	{
		ft_lst_rm(&ps->env, (d = new_dict(ps->args[i], 0)),
			cmp_dict_keys, del_dict);
		free(d);
	}
	return (1);
}

int	msh_env(struct s_process *ps)
{
	ft_lstiter(ps->env, dict_print);
	return (1);
}
