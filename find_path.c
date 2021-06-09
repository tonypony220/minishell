#include "minishell.h"

int path_executable(char *name)
{
	struct stat buf;
	int i;

	ft_memset(&buf, 0, sizeof(buf));
	i = !stat(name, &buf) && (S_IXUSR & buf.st_mode);
	//printf("\t\texec %d %s \n", S_IXUSR & buf.st_mode, name);
	return (i);
}

void ft_str_to_lower(char *str)
{
	str--;
	while (*(++str))
		*str = ft_tolower(*str);
}


char *find_path(char *name)
/* waiting name without spaces in start
 * function will not fit for variables cause they case sensitive
 * todo different handlingn of returned NULL in cases with '/' or without
 * todo join(char **arr) function */
{
	char **env_paths;
	char **mem;
	char *path;
	char *mid;

	env_paths = ft_split(getenv("PATH"), ':');
	mem = env_paths;
	while(*env_paths)
	{
		if (path_executable((path = ft_strjoin(
				*env_paths, (mid = ft_strjoin("/", name))))))
		{
			free(mid);
			break;
		}
		free(path);
		free(mid);
		path = 0;
		env_paths++;
	}
	freemultalloc((void**)mem);
	return (path);
}


void tst_find_path(void)
{
	char *path[] = {"cat", "less", "cor", "/bin/cat", "./asdf", "./a.out", 0};
	int i = 0;
	while (path[i])
	{
		printf("%s >> %s\n",  path[i], find_path(path[i]));
		i++;
	}
}
