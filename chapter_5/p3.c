#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	printf("Beginning (pid:%d)\n", (int) getpid() );
	int rc = fork();
	if (rc < 0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);
	} 
	else if (rc == 0)									// child
	{
		printf("Child (pid:%d)\n", (int) getpid() );
		char* args[3];
		args[0] = strdup("wc");
		args[1] = strdup("p3.c");
		args[2] = NULL;
		execvp(args[0], args);
	}
	else												// parent
	{	
		int rc_wait = wait(NULL);
		printf("Parent of %d (pid:%d)\n", rc_wait, (int) getpid() );
	}
	return 0;
}