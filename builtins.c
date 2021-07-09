#include "minishell.h"

int					msh_echo(struct process *ps)
{
	int				i;

	i = 1;
	!ft_strcmp(ps->args[1], "-n") && (i = 2);
	while (ps->args[i])
	{
		/* assume will not be case with empty commands */
		*ps->args[i] == '$'
		&& ((ps->args[i][1] != '?' && printf("%s", getenv(ps->args[i] + 1))) // todo this is wrong
		 	||
		 	(ps->args[i][1] == '?' && printf("%d", ps->exit_code)));
		*ps->args[i] != '$' && printf("%s", ps->args[i]);
		i++;
	}
	!ft_strcmp(ps->args[1], "-n") && printf("\n");
	return (1);
}

int					msh_export(struct process *ps)
{
	char			**key_value;
	int				ret;

	if (ps->args[1])	
	{	
			
		if (!(key_value = ft_split(*ps->args[1], '=')))
			return (0);
		ret = dict_set_default(ps->env, key_value[0], key_value[1]);
		free(key_value);
		return (ret);
	}
	else
	{
		ft_lst_sort_bubble(&ps->env, cmp_dict_keys);
		ft_lstiter(ps->env, env_dict_print);
	}
	return (1);
}

int					msh_unset(struct process *ps)
{
	struct dict *d;

	ft_lst_rm(&ps->env, (d = new_dict(ps->args[1], 0)),
			  cmp_dict_keys, del_dict);
	free(d);
	return (1);
}

int					msh_env(struct process *ps)
{
	ft_lstiter(ps->env, dict_print);
	return (1);
}

/* function return always ok because prints error directly */
int					msh_pwd(struct process *ps)
{
	char buf[MAXPATHLEN];
	//char *buf;

	//printf(GREEN"%s getcwd <<\n"RESET, getcwd(buf, sizeof(buf)));
	(getcwd(buf, sizeof(buf)) && printf("%s\n", buf)) || display_err(ps);
	//getcwd(buf, sizeof(buf)) && printf("%s\n", sizeof(buf)) || display_err(ps);
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
int					msh_cd(struct process *ps)
{
	char buf[MAXPATHLEN];
	char *path;
	int r;

	path = ps->args[1];
	(r = chdir(path)) && display_err(ps);
	if (r) 
		return (-1);
	getcwd(buf, sizeof(buf));
	r = dict_set_default(ps->env, ft_strdup("PWD"), ft_strdup(buf));
//	printf("%d << r\n", r);
	return (r);
}


int					msh_exit(struct process *ps)
{
	return (1);
}













