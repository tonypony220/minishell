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


char *find_path(char *name)
/* waiting name without spaces in start
 * todo different handlingn of returned NULL in cases with '/' or without */
{
	char **env_paths;
	char *path;
	char *s;

	path = (char*)((unsigned long)name * (name[0] == '/' || name[0] == '.'));
	(!path && (s = getenv("PATH"))) || (s = "");
	env_paths = ft_split(s, ':');
	while(*env_paths)
	{
		if (!path
			&& path_executable(ft_strjoin(*env_paths, ft_strjoin("/", name))))
			path = ft_strjoin(*env_paths, ft_strjoin("/", name));
		else
			free(*env_paths);
		env_paths++;
	}
	(path
	 && path_executable(path)
	 && (path = ft_strdup(path)))
	|| (path = 0);
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
