#include "minishell.h"

int	msh_heredoc(struct process *ps)
{
	write(1, ps->args[0], ft_strlen(ps->args[0]));
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
int	msh_cd(struct process *ps)
{
	char	buf[MAXPATHLEN];
	char	*path;
	int		r;

	path = ps->args[1];
	(r = chdir(path)) && display_err(ps);
	if (r)
		return (-1);
	getcwd(buf, sizeof(buf));
	r = dict_set_default(ps->env, ft_strdup("PWD"), ft_strdup(buf));
	return (r);
}

int	msh_exit(struct process *ps)
{
	printf("exit\n");
	free_and_null(ps->shell->heredoc, ps->shell->line);
	ft_lstclear(&ps->shell->cmd, free_process);
	ft_lstclear(&ps->shell->env, del_dict);
	exit(0);
	return (1);
}

/* function return always ok because prints error directly */
int	msh_pwd(struct process *ps)
{
	char	buf[MAXPATHLEN];

	(getcwd(buf, sizeof(buf)) && printf("%s\n", buf)) || display_err(ps);
	return (1);
}
