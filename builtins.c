#include "minishell.h"

int yosh_echo(struct process *ps)
{
	int i;

	i = 1;
	!ft_strcmp(ps->args[1], "-n") && (i = 2);
	while (ps->args[i])
	{
		/* assume will not be case with empty commands */
		*ps->args[i] == '$'
		&& ((ps->args[i][1] != '?' && printf("%s", getenv(ps->args[i] + 1))) // todo this is wrong
		 	||
		 	(ps->args[i][1] == '?' && printf("%d", last_exit_code)));
		*ps->args[i] != '$' && printf("%s", ps->args[i]);
		i++;
	}
	!ft_strcmp(ps->args[1], "-n") && printf("\n");
	return (1);
}