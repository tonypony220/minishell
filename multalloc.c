#include "minishell.h"

int	arr_len(void **p)
{
	int		i;

	i = 0;
	while (*p && ++i)
		p++;
	return (i);
}

int	printmultalloc(void **p)
{
	int	i;

	i = -1;
	while (*p)
	{
		printf(CYAN"\t*arr[i%d]=(%s)"RESET"\n", ++i, (char *)*p);
		p++;
	}
	return (1);
}

int	freemultalloc(void **p)
{
	void	**tmp;

	tmp = p;
	while (p && *p)
	{
		free(*p);
		p++;
	}
	free(tmp);
	return (1);
}

void	**multalloc(int rows, int columns, unsigned long size)
{
	void	**x;
	int		i;

	x = malloc(sizeof(void *) * (rows + 1));
	if (!x)
		return (0);
	ft_memset(x, 0, sizeof(void *) * (rows + 1));
	i = -1;
	while (++i < rows)
	{
		*(x + i) = malloc(size * columns);
		if (!(*(x + i)) && freemultalloc(x))
			return (0);
		ft_memset(x[i], 0, size);
	}
	return (x);
}
