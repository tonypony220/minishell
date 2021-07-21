#include "minishell.h"

int	msh_heredoc(struct s_process *ps)
{
	int		fd;
	char	*buff;
	int		r;

	fd = open(ps->args[0], O_RDONLY, 0644);
	buff = malloc(2);
	r = 1;
	while (r)
	{
		r = read(fd, buff, 2);
		write(1, buff, r);
	}
	free(buff);
	unlink(ps->args[0]);
	exit(0);
	return (1);
}

/* cd . 
 * 	  .. 
 * 	  ../path 
 *	  /path
 *
 * returns:	
 *	  0 - malloc fail	
 *	  1 - ok
 *	 -1 - bad dir
 */
int	msh_cd(struct s_process *ps)
{
	char	buf[MAXPATHLEN];
	char	*path;
	int		r;

	(path = ps->args[1]) || (path = my_getenv(ps->env, "HOME"), ':');
	(path || display_err_direct(ps->args[0], "HOME not set"));
	if (!path)
		return (0);
	(r = chdir(path)) && display_err(ps);
	if (r)
		return (-1);
	getcwd(buf, sizeof(buf));
	r = dict_set_default(ps->env, ft_strdup("PWD"), ft_strdup(buf));
	return (r);
}

int	msh_exit(struct s_process *ps)
{
	int		code;

	if (*ps->flag)
		return (0);
	printf("exit\n");
	code = ps->shell->last_exit_code;
	free_and_null(ps->shell->heredoc, ps->shell->line);
	ft_lstclear(&ps->shell->env, del_dict);
	ft_lstclear(&ps->shell->cmd, free_process);
	exit(code);
	return (1);
}

/* function return always ok because prints error directly */
int	msh_pwd(struct s_process *ps)
{
	char	buf[MAXPATHLEN];

	(getcwd(buf, sizeof(buf)) && printf("%s\n", buf)) || display_err(ps);
	return (1);
}
