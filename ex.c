#include <unistd.h>
int main()
{
	char* argv[] = { "jim", "jams", NULL };
	char* envp[] = { "some", "environment", NULL };
  	if (execve("jim", argv, envp) == -1)
		perror("Could not execve");
  return 1;
}
