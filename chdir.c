#include "minishell.h"

int main()
{
	char *buf = 0;

	if(chdir(""))
		perror("shit");
	printf("CWD %s\n", getcwd(buf, 0));
	printf("PWD %s\n", getenv("PWD"));
	//system("pwd");
}
