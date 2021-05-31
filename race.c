int main()
{
	int ppid = getpid(); /* ppid is the parent id */
	if (fork() > 0)  /* parent */
		exit(0); //write(1, "a\n", 2);
   	else 
	{ /* child */ 
		if (ppid == getppid()) 
			 write(1, "parent alive\n", 13);  /* if child gets CPU */
		else write(1, "parent dead\n", 12);   /* if parent gets CPU */
}
