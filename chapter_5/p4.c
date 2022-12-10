#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
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
		close(STDOUT_FILENO);
		open("p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		
		char* args[3];
		args[0] = strdup("wc");
		args[1] = strdup("p4.c");
		args[2] = NULL;
		execvp(args[0], args);
	}
	else												// parent
	{	
		int rc_wait = wait(NULL);
	}
	return 0;
}