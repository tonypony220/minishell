#include "minishell.h"

int	path_executable(char *name)
{
	struct stat	buf;
	int			i;

	ft_memset(&buf, 0, sizeof(buf));
	i = !stat(name, &buf) && (S_IXUSR & buf.st_mode);
	return (i);
}

void	ft_str_to_lower(char *str)
{
	str--;
	while (*(++str))
		*str = ft_tolower(*str);
}

/* waiting name without spaces in start
 * function will not fit for variables cause they case sensitive
 * todo different handlingn of returned NULL in cases with '/' or without
 * todo join(char **arr) function */
char	*find_path(struct s_process *ps, char *name)
{
	char	**env_paths;
	char	**mem;
	char	*path;
	char	*mid;

	path = 0;
	env_paths = ft_split(my_getenv(ps->env, "PATH"), ':');
	if (env_paths == NULL)
		return (NULL);
	mem = env_paths;
	while (*env_paths && *name != '\0')
	{
		path = ft_strjoin(*env_paths, (mid = ft_strjoin("/", name)));
		if (path_executable(path))
		{
			free(mid);
			break ;
		}
		free(path);
		free(mid);
		path = NULL;
		env_paths++;
	}
	freemultalloc((void **)mem);
	return (path);
}

char	*my_getenv(t_list *env, char *key)
{		
	t_list			*one;
	struct s_dict	*d;
	char			*value;

	one = ft_lst_find(env, (d = new_dict(key, 0)),
			cmp_dict_keys);
	if (one)
	{
		value = dict_value(one->content);
		free(d);
		return (value);
	}
	free(d);
	return (NULL);
}
