#include <stdio.h>
#include <stdlib.h>
int main(int ac, char **av)
{
	int i; 
	i = -1;
	char *env = getenv("some");
	printf("%s\n", env);
	printf("%s\n", getenv("PATH"));
	while (i++ < ac - 1)
		printf("%s\n", av[i]);

}
