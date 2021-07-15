#include "minishell.h"

int					msh_heredoc(struct process *ps)
{
	write(1, ps->args[0], ft_strlen(ps->args[0]));
	exit(0);
	return (1);
}
