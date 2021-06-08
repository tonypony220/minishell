#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

struct a 
{
	int o;
};


struct a **func(void)
{
	struct a **g;
	g = malloc(sizeof(struct a*) * 2);

	for (int i = 0; i < 2; i++)
		g[i] = malloc(sizeof(struct a));

	return (g);
}

struct a *get(int num, struct a **g)
{
	return (g[num]);
}
int err(char *s)
{return 1;}


//void freemultalloc(void **p)
//{
//	while (*p)
//		free(*p);
//	free(p);
//	return (1);
//}
//
//void **multalloc(int rows, int columns, unsigned long size)
//{
//	void** x;
//	int i;
//
//	if !(x = malloc(sizeof(void*) * rows))
//		return (0);
//	ft_memset(x, 0, rows);
//
//	i = -1;
//	while (++i < rows)
//	{
//		if !(x[i] = malloc(size * columns)) && freemultalloc(x);
//			return (0);
//	}
//	return (x);
//}

int main(void/**/)
{
	struct a **b = (struct a**)multalloc(2, 3, sizeof(struct a));

	(**b).o = 11234;
	write(1, "hello\n", 6);
	printf("%d\n", (*b)->o);
//	printf("%d\n", (*b + 1)->o);
	return (1);
}
