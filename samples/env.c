#include <stdio.h>
#include <stdlib.h> // environ
#include <string.h>
extern char** environ;

// NULL + ard < 0x08048000 => means NULL adress was used in pointer arithmetic

int main(void)
{
	char** p = environ;

	printf("%s\n", getenv("PWD"));
	//while (*environ)
	//{
	//	//printf("%s\n", *environ);
	//	*environ = 0;
	//	environ++;
	//}
	unsetenv("PWD");
	setenv("BO", "VAL", 0);
	printf("%s\n", getenv("BO"));
	while (*environ)
	{
		if (strncmp(*environ, "BO", 2))
		{
			printf("found!\n");
			free(*environ);
		}
		environ++;
	}
	printf("%s\n", getenv("PWD"));
	environ = p;
}
