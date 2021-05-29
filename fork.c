#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		main()
{

	int	pid;
	int stat;

	printf("pid %d %d\n", getpid(), 0);
	if ((pid = fork()) == -1)
	{
		perror("demo");
		exit(1);
	}
	else if (pid == 0)
	{
		//write(1, "child\n", 6);
		printf("child pid %d getpid %d getppid %d\n", pid, getpid(), getppid());
		//exit(0);
		//printf("child");
	}
	else
	{
		// write(1, "parent\n", 7);
		wait(&stat);		
		printf("parent pid %d getpid %d getppid %d\n", pid, getpid(), getppid());
	}
	if (WIFEXITED(stat))  /* << True if the process terminated normally by a call to _exit(2) or exit(3). */
		/* If WIFEXITED(status) is true, WEXITSTATUS evaluates to the low-order 
		 * 8 bits of the argument passed to _exit(2) or exit(3) by the child. */
       printf("Exit status: %d\n", WEXITSTATUS(stat));  
	else if (WIFSIGNALED(stat)) /* True if the process terminated due to receipt of a signal. */
			psignal(WTERMSIG(stat), "Exit signal");

	//write(1, "string\n", 7);
		

	int ppid = getpid(); /* ppid is the parent id */
	if (fork() > 0)  /* parent */
		exit(0); //write(1, "a\n", 2);
   	else 
	{ /* child */ 
		if (ppid == getppid()) 
			 write(1, "parent alive\n", 13);  /* if child gets CPU */
		else write(1, "parent dead\n", 12);   /* if parent gets CPU */
	}
}
