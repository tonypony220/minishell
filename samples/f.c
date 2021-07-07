#include <sys/wait.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	err(char* err_str)
{
	perror(err_str);
	exit(1);
	return 1;
}

int func()
{
	int pid;

	if ((pid = fork()) == -1)
	{
		perror("demo");
		exit(1);
	}
	else if (pid == 0)   				/* child:  "cat a"                      */
	{  
		sleep(100);
		_exit(1);        				/* no flush                             */
	}
	else 
	{                      				/* parent:  "/usr/bin/wc"               */
		sleep(100);
		exit(1);	        			/* parent flushes                       */
	}
}

int main()
{

	func();
}
