#include "minishell.h"

/* don't know how to force return int that compiler accept it */
int	err(char *err_str)
{
	write(2, err_str, ft_strlen(err_str));
	exit(1);
	return (1);
}

/* function calls on getcwd failed as well */
char	*make_err_msg(struct s_process *ps)
{
	if (ps->exit_code)
	{
		if (ps->exit_code == CMD_NOT_FOUND_CODE)
			return ("command not found");
		return (strerror(ps->exit_code));
	}
	return (strerror(errno));
}

int	display_err(struct s_process *ps)
{
	char	*arg;

	arg = *(ps->args);
	ps->fd[IN] == -1 && (arg = ps->file[IN]);
	ps->fd[OUT] == -1 && (arg = ps->file[OUT]);
	printf(RED""SHELL_NAME": %s: %s"RESET"\n", arg, make_err_msg(ps));
	return (1);
}

int	display_err_direct(char *arg, char *msg)
{
	printf(SHELL_NAME": %s: %s\n", arg, msg);
	return (1);
}
