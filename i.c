#include <stdlib.h>
#include <stdio.h>
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

int main(void)
{
	struct a **b = func();

	//get(1, b)->o = 10;
	(*b[1]).o = 10;
	printf("%d", (*b)->o);
}
