
#include "mini_parser.h"

int		space_skip(const char *nptr, t_shell *shell)
{
	while ((nptr[shell->i] == ' ') || (nptr[shell->i] == '\n')
		|| (nptr[shell->i] == '\f') || (nptr[shell->i] == '\v')
		|| (nptr[shell->i] == '\r') || (nptr[shell->i] == '\t'))
		(shell->i)++;
	return (1);
}

void	ft_putendl(char *s, int endl)
{
	size_t	i;

	i = -1;
	if (s)
	{
		while (s[++i])
			write(1, &s[i], 1);
	}
	if (endl == 1)
		write(1, "\n", 1);
}
