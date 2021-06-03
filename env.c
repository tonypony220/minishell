#include <stdio.h>
#include <stdlib.h> // environ
extern char** environ;

// NULL + ard < 0x08048000 => means NULL adress was used in pointer arithmetic

int main(void)
{
	printf("%s\n", getenv("LANG"));
	while (*environ)
	{
		printf("%s\n", *environ);
		environ++;
	}

}
