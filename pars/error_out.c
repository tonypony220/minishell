#include "../minishell.h"

int	error_out(t_shell *shell, char *error)
{
	ft_putendl("bash: ", 0);
	ft_putendl(error, 1);
	return (shell->err = -1);
}
