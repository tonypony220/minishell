#include "../minishell.h"

int	error_out(t_shell *shell)
{
	if (shell->err < 0 && shell->err > -5)
	{
		printf("bash: syntax error %s\n", shell->err_msg);
		return (-1);
	}
	if (shell->err == -5)
		printf("Malloc error\n");
	if (shell->err == -6)
		write(1, "\r", 1);
	return (0);
}

int	set_error(t_shell *shell, int error)
{
	if (shell->err < 0)
		return (-1);
	shell->err = error;
	shell->last_exit_code = 2;
	if (error == -1)
		shell->err_msg = "single quotes";
	if (error == -2)
		shell->err_msg = "double quotes";
	if (error == -3)
		shell->err_msg = "near unexpected token '|'";
	if (error == -4)
		shell->err_msg = "near unexpected token 'newline'";
	return (-1);
}
