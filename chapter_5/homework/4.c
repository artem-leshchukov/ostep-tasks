#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	int rc = fork();
	if (rc < 0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);
	} 
	else if (rc == 0)									// child
	{
		char* args[3];
		args[0] = strdup("ls");
		args[1] = NULL;
		args[2] = NULL;
		execvp(args[0], args);
	}
	else												// parent
	{	
		int rc_wait = wait(NULL);
	}
	return 0;
}