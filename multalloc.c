#include "minishell.h"

int			arr_len(void **p)
{
	int		i;

	i = 0;
	while (*p && ++i)
	{
		printf("%p %d \n", *p, i);
		p++;
	}
	return (i);
}

int			freemultalloc(void **p)
{
	while (*p)
		free(*p);
	free(p);
	return (1);
}

/* now it's multcalloc function */
void		**multalloc(int rows, int columns, unsigned long size)
{
	void	**x;
	int		i;

	if (!(x = malloc(sizeof(void*) * (rows + 1))))
		return (0);
	ft_memset(x, 0,sizeof(void*) * (rows + 1));
	printf("arr_len %d \n", arr_len(x));

	i = -1;
	while (++i < rows)
	{
		write(1, "new column\n", 11);
		if (!(*(x + i) = malloc(size * columns)) && freemultalloc(x))
			return (0);
		ft_memset(x[i], 0, size);
	}
	return (x);
}