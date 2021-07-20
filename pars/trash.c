#include "../minishell.h"

void	print_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		printf("TOKEN=[%s][%d]\n", tmp->token, tmp->redir_type);
		tmp = tmp->next;
	}
}
