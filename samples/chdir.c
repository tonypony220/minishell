#include "minishell.h"

int main()
{
	//char *buf = 0;
	char buf[MAXPATHLEN];

	if(chdir(""))
		perror("shit");
	printf("CWD %s\n", getcwd(buf, sizeof(buf)));
	printf("CWD %s\n", buf);
	printf("PWD %s\n", getenv("PWD"));
	//system("pwd");
}
