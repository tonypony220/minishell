#include "minishell.h"

void	dispatch_status(struct process *ps)
{
	char	**arr;

	ps->path = ft_strdup(ps->args[0]);
	arr = ft_split(UPPER_EXCLUDED_BUILTINS, ' ');
	if (!ft_str_in_strs(ps->path, arr))
		ft_str_to_lower(ps->path);
	freemultalloc((void **)arr);
	arr = ft_split(SELF_BUILTINS, ' ');
	(ft_str_in_strs(ps->path, arr)) && (ps->status |= DIRECT);
	freemultalloc((void **)arr);
	!ft_strcmp("export", ps->path) && ps->args[1] && (ps->status |= DIRECT);
	arr = ft_split(BUILTINS, ' ');
	ft_str_in_strs(ps->path, arr) && (ps->status |= BUILTIN);
	freemultalloc((void **)arr);
}

/* executable name should be lower case */
void	dispatching_process(struct process *ps)
{
	char	*name;

	name = 0;
	dispatch_status(ps);
	if (ps->status & BUILTIN || *ps->path == '/' || *ps->path == '.')
		return ;
	name = find_path(ps->path);
	if (name)
	{
		free(ps->path);
		ps->path = name;
	}
	else
	{
		(*ps).exit_code = CMD_NOT_FOUND_CODE;
		display_err(ps);
	}
}
